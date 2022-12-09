/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:20 by dpark             #+#    #+#             */
/*   Updated: 2022/12/09 21:17:57 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool    _pickup(t_philo *philo, t_data *data)
{
    if(pthread_mutex_lock(&data->forks[philo->l]) || \
        pthread_mutex_lock(&data->forks[philo->r]) || \
        !print_status(PICKUP, philo->id, data))
        return(false);
    return(true) ;
}

bool    _putdown(t_philo *philo, t_data *data)
{
    // unlock => unlock ok ? fail ?
    if(pthread_mutex_unlock(&data->forks[philo->l]) || \
        pthread_mutex_unlock(&data->forks[philo->r]))
        return(false);
    return(true);
}

bool    _sleep(t_philo *philo, t_data *data)
{
    if (!get_timestamp(&philo->cur))
        return(false);
    print_status(SLEEPING, philo->id, data);
    if (!wait_interval(data->time_to_sleep, philo->cur))
        return(false);
    return(true);
}

bool    _eating(t_philo *philo, t_data *data)
{
    // 화장실 마려워 => 다왔다. => 닫을려고... 하는데... => 아..... 1초만 빨랐다면....
    if (!get_timestamp(&philo->cur) || !_pickup(philo, data))
        return(false);
    print_status(EATING, philo->id, data);
    if (!wait_interval(data->time_to_eat, philo->cur) || \
        !_putdown(philo, data))
        return(false);
    (philo->eat_cnt)++;
    return(true);
}

bool    _thinking(t_philo *philo, t_data *data)
{
    print_status(THINKING, philo->id, data);
    return(true);
}

//철학자수 / 죽는시간 / 먹는데걸리는시간 / 자는데걸리는시간