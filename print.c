/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:32 by dpark             #+#    #+#             */
/*   Updated: 2022/12/11 13:58:30 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
**/

bool    get_timestamp(long long *ret)
{
    struct timeval t;
    if (gettimeofday(&t, NULL) == -1)
        return(false);
    *ret = (long long)((t.tv_sec * MILLI) + (t.tv_usec / MILLI));
    return (true);
}

bool    print_status(t_status status, int id, t_data  *data)
{
    long long intaval;
    long long cur;

    if (!get_timestamp(&cur) || pthread_mutex_lock(&data->print))
        return(false);
    intaval = cur - data->start_time;
    if (status == PICKUP)
        printf("%lld %d has taken a fork\n", intaval, id);
    if (status == EATING)
        printf("%lld %d is eating\n", intaval, id);
    if (status == SLEEPING)
        printf("%lld %d is sleeping\n", intaval, id);
    if (status == THINKING)
        printf("%lld %d is thinking\n", intaval, id);
    if (status == DIED)
        printf("%lld %d died\n", intaval, id);
    if (pthread_mutex_unlock(&data->print))
        return(false);
    return (true);
}
