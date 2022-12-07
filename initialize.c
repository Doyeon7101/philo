#include "philo.h"
//id, l, r, eat_cnt, status
bool set_philo(t_philo *philo, t_data *data)
{
    int i;
    int philo_num;

    i = 0;
    philo_num = data->num_of_philo;
    while (i < philo_num)
    {
        philo[i].id = i;
        philo[i].l = (i + 1) % philo_num;
        philo[i].r = i;
        philo[i].eat_cnt = 0;
        philo[i].data = data;
        if (!pthread_create(&philo[i].philo_t, NULL, routine, &philo[i]))
            return (false);
    }
    return (true);
}

bool init_mutex(t_data *data)
{
    int i;

    data->forks = calloc(data->num_of_philo, sizeof(pthread_mutex_t));
    if (!data->forks)
        return(false);
    i = 0;
    while (i < data->num_of_philo)
    {
        if (!pthread_mutex_init(&data->forks[i++], NULL));
            return(false);
    }
    if (!pthread_mutex_init(&data->print, NULL) || !pthread_mutex_init(&data->dining, NULL))
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
    return ;
}

bool init_parse(t_data *data, t_philo *philo, char **argv)
{
    t_philo *philos;
    int i;

    if (!set_argv(argv, data));
        return(false);
    philos = calloc(data->num_of_philo, sizeof(t_philo));
    if (!philos)
        return(false);
    if (!set_philo(philo, data));
    return ;
}