/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:37 by dpark             #+#    #+#             */
/*   Updated: 2022/12/09 18:16:38 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
bool bool_atoi(int *dst, const char *str)
{
	long	r;
	int		i;

	r = 0;
	i = 1;
	while (*str == ' ' || *str == '\t' || *str == '\r' \
		|| *str == '\n' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		r *= 10;
		r += *str - 48;
		str++;
	}
	if (*str != '\0')
		return(false);
	*dst = r * i;
	return(true) ;
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

bool    wait_interval(int time, long long start_time)
{
    long long cur;

    if (!get_timestamp(&cur))
        return(false);
    while (cur - start_time <= time)
    {
        if (usleep(EPSILON))
            return(false);
    	if (!get_timestamp(&cur))
    	    return(false);
    }
    return(true);
}
