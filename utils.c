/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:37 by dpark             #+#    #+#             */
/*   Updated: 2022/12/09 21:43:55 by dpark            ###   ########.fr       */
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

	if (!get_timestamp(&cur))
		return (false);
	while (cur - start_time <= time)
	{
		if (usleep(EPSILON))
			return (false);
		if (!get_timestamp(&cur))
			return (false);
	}
	return (true);
}
