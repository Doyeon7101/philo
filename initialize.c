#include "philo.h"
//id, l, r, eat_cnt, status
void set_philo(t_philo *philo, t_data *data)
{
    int i;
    int philo_num;

    i = 0;
    philo_num = data->num_of_philo;
    while (i < philo_num)
    {
        philo[i].id = i;
        philo[i].l = (i + philo_num - 1) % philo_num;
        philo[i].r = (i + 1) % philo_num;
        philo[i].eat_cnt = 0;
        philo[i].data = data;
        philo[i].state = THINKING;
        if (!pthread_create(&philo[i].philo_t, NULL, routine, &philo[i]))
            ft_printerror("failed to create thread");
    }
    return ;
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
    if (!pthread_mutex_init(&data->print, NULL) || !pthread_mutex_init(&data->, NULL))
        return(false);
    return(true);
}

bool    set_argv(char **argv, t_data *data)
{
    ft_atoi(&data->num_of_philo, *++argv);
    ft_atoi(&data->time_to_die, *++argv);
    ft_atoi(&data->time_to_eat, *++argv);
    ft_atoi(&data->time_to_sleep, *++argv);
    if (!*++argv)
        data->must_eat_num = -1;
    else
        ft_atoi(&data->must_eat_num, *argv);
    if (!init_mutex(data))
        return (false);
    return ;
}

void    initialize(t_data *data, t_philo *philo, char **argv)
{
    t_philo *philos;
    int i;

    if (!set_argv(argv, data));
        ft_printerror("initialization failed");
    philos = calloc(data->num_of_philo, sizeof(t_philo));
    if (!philos)
        ft_printerror("calloc failed");
    set_philo(philo, data);
    return ;
}