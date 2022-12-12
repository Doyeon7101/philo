/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:03 by dpark             #+#    #+#             */
/*   Updated: 2022/12/12 15:26:41 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!get_timestamp(&philo->cur))
		pthread_mutex_unlock(&philo->data->dining);
	if (philo->id % 2)
		wait_interval(10 * EPSILON, philo->cur);
	while (1)
	{
		_eating(philo, philo->data);
		_sleep(philo, philo->data);
		_thinking(philo, philo->data);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo		*philo;
	long long	cur;
	long long	time_to_die;
	int			i;

	philo = (t_philo *)arg;
	time_to_die = philo->data->time_to_die;
	if (!get_timestamp(&cur))
		pthread_mutex_unlock(&philo->data->dining);
	wait_interval(time_to_die - EPSILON, cur);
	while (42)
	{
		i = -1;
		while (++i < philo->data->num_of_philo)
		{
			if (!get_timestamp(&cur))
				pthread_mutex_unlock(&philo->data->dining);
			if (cur - philo[i].cur >= time_to_die)
			{
				print_status(DIED, philo[i].id, philo[i].data);
				pthread_mutex_unlock(&philo->data->dining);
				return (0);
			}
		}
	}
}

bool	set_philo(t_philo *philo, t_data *data)
{
	int			i;
	pthread_t	th_monitor;

	i = -1;
	if (!get_timestamp(&data->start_time) || \
			pthread_mutex_lock(&data->dining))
		return (false);
	while (++i < data->num_of_philo)
	{
		philo[i].id = i;
		philo[i].l = (i + 1) % data->num_of_philo;
		philo[i].r = i;
		philo[i].eat_cnt = 0;
		philo[i].data = data;
		if (pthread_create(&philo[i].philo_t, NULL, routine, &philo[i]) || \
			pthread_detach(philo[i].philo_t))
			return (false);
	}
	if (pthread_create(&th_monitor, NULL, monitor, philo) || \
		pthread_detach(th_monitor))
		return (false);
	if (pthread_mutex_lock(&data->dining))
		return (false);
	return (true);
}

bool	set_argv(char **argv, t_data *data)
{
	if (!bool_atoi(&data->num_of_philo, *++argv) || \
		!bool_atoi(&data->time_to_die, *++argv) || \
		!bool_atoi(&data->time_to_eat, *++argv) || \
		!bool_atoi(&data->time_to_sleep, *++argv))
		return (false);
	if (!*++argv)
		data->must_eat_num = -1;
	else
	{
		if (!bool_atoi(&data->must_eat_num, *argv))
			return (false);
	}
	if (!init_mutex(data))
		return (false);
	data->eat_cmplt = 0;
	return (true);
}

bool	init_parse(t_data *data, t_philo *philo, char **argv)
{
	t_philo	*philos;
	int		i;

	if (!set_argv(argv, data))
		return (false);
	philos = ft_calloc(data->num_of_philo, sizeof(t_philo));
	if (!philos)
		return (false);
	if (!set_philo(philo, data))
		return (false);
	return (true);
}
