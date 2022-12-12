/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:37 by dpark             #+#    #+#             */
/*   Updated: 2022/12/12 15:27:02 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	bool_atoi(int *dst, const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - 48;
		str++;
	}
	if (*str != '\0')
		return (false);
	if (num > 2147483647)
		return (false);
	*dst = num;
	return (true);
}

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*ret;
	int		n;
	void	*ptr;

	ret = (void *)malloc(size * cnt);
	n = cnt * size;
	ptr = ret;
	if (!ret)
		return (NULL);
	while (n-- > 0)
	{
		*(char *)ptr = 0;
		++ptr;
	}
	return (ret);
}

bool	wait_interval(int time, long long start_time)
{
	long long	cur;

	while (1)
	{
		if (!get_timestamp(&cur))
			return (false);
		if (cur - start_time >= time)
			return (true);
		if (usleep(EPSILON))
			return (false);
	}
	return (true);
}

bool	init_mutex(t_data *data)
{
	int	i;

	data->forks = ft_calloc(data->num_of_philo, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (false);
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (false);
	}
	if (pthread_mutex_init(&data->print, NULL) || \
		pthread_mutex_init(&data->dining, NULL))
		return (false);
	return (true);
}
