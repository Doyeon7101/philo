/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpark <dpark@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:16:03 by dpark             #+#    #+#             */
/*   Updated: 2022/12/11 14:11:11 by dpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    get_timestamp(&philo->cur);
    if(philo->id % 2)
        wait_interval(30 * EPSILON, philo->cur);
    while(1)
    {
        if (!_eating(philo, philo->data))
            printf("eating fail\n");
        if (!_sleep(philo, philo->data))
            printf("sleep fail\n");
        if (!_thinking(philo, philo->data))
            printf("thinking fail\n");
        // lock
        // finish ? end : continue; => t_data 1 or philo 1
        // unlock
    }
    return (0);
}

bool set_philo(t_philo *philo, t_data *data)
{
    int i;
    int philo_num;

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
        // sleep(1);
    }
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