/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:03 by dpark             #+#    #+#             */
/*   Updated: 2022/12/12 11:26:31 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * - philo act 오오류류처리
 * - monitor 구현
 * - 200명 넘어가는 숫자.... 어칼거야
 **/
void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if(get_timestamp(&philo->cur) || philo->id % 2)
        wait_interval(10 * EPSILON, philo->cur);
    while(1)
    {
        _eating(philo, philo->data);
        _sleep(philo, philo->data);
        _thinking(philo, philo->data);
    }
    return (0);
}

void    *monitor(void *arg)
{
    t_philo *philo;
    long long cur;

    int i;

    philo = (t_philo *)arg;
    if (!get_timestamp(&cur))
        pthread_mutex_unlock(&philo->data->dining);
    wait_interval(philo->data->time_to_die - EPSILON, cur);
    while (42)
    {
        i = -1;
        while (++i > philo->data->num_of_philo)
        {
            if (!get_timestamp(&cur))
                pthread_mutex_unlock(&philo->data->dining);
            if (cur - philo[i].cur > philo->data->time_to_die) // dining 시작 시간보다 죽어야 하는 시간이 더 짧을경우 
            {
                print_status(DIED, philo[i].id, philo[i].data);
                pthread_mutex_unlock(&philo->data->dining);
            }
        }
    }
}

bool set_philo(t_philo *philo, t_data *data)
{
    int         i;
    int         philo_num;
    pthread_t   th_monitor;

    i = -1;
    philo_num = data->num_of_philo;
    if (!get_timestamp(&data->start_time) || \
         pthread_mutex_lock(&data->dining))
        return(false);
    while (++i < philo_num)
    {
        philo[i].id = i;
        philo[i].l = (i + 1) % philo_num;
        philo[i].r = i;
        philo[i].eat_cnt = 0;
        philo[i].data = data;
        if (pthread_create(&philo[i].philo_t, NULL, routine, &philo[i]) || \
            pthread_detach(philo[i].philo_t))
            return (false);
    }
    if (pthread_create(&th_monitor, NULL, monitor, philo) || \
        pthread_detach(th_monitor))
            return(false);
    if(pthread_mutex_lock(&data->dining))
        return(false);
    return (true);
}

bool init_mutex(t_data *data)
{
    int i;

    data->forks = ft_calloc(data->num_of_philo, sizeof(pthread_mutex_t));
    if (!data->forks)
        return(false);
    i = -1;
    while (++i < data->num_of_philo)
    {
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (false);
    }
    if (pthread_mutex_init(&data->print, NULL) ||\
        pthread_mutex_init(&data->dining, NULL))
        return(false);
    return(true);
}

bool    set_argv(char **argv, t_data *data)
{
    if(!bool_atoi(&data->num_of_philo, *++argv) || !bool_atoi(&data->time_to_die, *++argv) ||\
     !bool_atoi(&data->time_to_eat, *++argv) || !bool_atoi(&data->time_to_sleep, *++argv))
        return(false);
    if (!*++argv)
        data->must_eat_num = -1;
    else
    {
        if (!bool_atoi(&data->must_eat_num, *argv))
            return(false);
    }
    if (!init_mutex(data))
        return (false);
    return (true);
}

bool init_parse(t_data *data, t_philo *philo, char **argv)
{
    t_philo *philos;
    int i;

    if (!set_argv(argv, data))
        return(false);
    philos = ft_calloc(data->num_of_philo, sizeof(t_philo));
    if (!philos)
        return(false);
    if (!set_philo(philo, data))
        return(false);
    return (true);
}