/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:20 by dpark             #+#    #+#             */
/*   Updated: 2022/12/12 15:07:28 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	_pickup(t_philo *philo, t_data *data)
{
	if (pthread_mutex_lock(&data->forks[philo->l]) || \
		pthread_mutex_lock(&data->forks[philo->r]) || \
		!print_status(PICKUP, philo->id, data))
		pthread_mutex_unlock(&data->dining);
}

void	_putdown(t_philo *philo, t_data *data)
{
	if (pthread_mutex_unlock(&data->forks[philo->l]) || \
		pthread_mutex_unlock(&data->forks[philo->r]))
		pthread_mutex_unlock(&data->dining);
}

void	_sleep(t_philo *philo, t_data *data)
{
	long long	cur;

	if (!get_timestamp(&cur) || !print_status(SLEEPING, philo->id, data))
		pthread_mutex_unlock(&data->dining);
	if (!wait_interval(data->time_to_sleep, cur))
		pthread_mutex_unlock(&data->dining);
}

void	_eating(t_philo *philo, t_data *data)
{
	_pickup(philo, data);
	if (!get_timestamp(&philo->cur))
		pthread_mutex_unlock(&data->dining);
	print_status(EATING, philo->id, data);
	if (!wait_interval(data->time_to_eat, philo->cur))
		pthread_mutex_unlock(&data->dining);
	_putdown(philo, data);
	(philo->eat_cnt)++;
	if (philo->eat_cnt >= philo->data->must_eat_num)
	{
		(philo->data->eat_cmplt)++;
		if (philo->data->eat_cmplt >= philo->data->num_of_philo)
		{
			print_status(COMPLETE, 0, data);
			pthread_mutex_unlock(&data->dining);
		}
	}
}

void	_thinking(t_philo *philo, t_data *data)
{
	print_status(THINKING, philo->id, data);
}
