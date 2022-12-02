#include "philo.h"
t_arg *set_argv(char *argv)
{
    t_arg *args;

    args = (t_arg *)malloc(sizeof(t_philo));
    if (!args)
        ft_printerror("malloc failed");
    args->num_of_philo = ft_atoi(*++argv);
    args->time_to_die = ft_atoi(*++argv);
    args->time_to_eat = ft_atoi(*++argv);
    args->time_to_sleep = ft_atoi(*++argv);
    if (*++argv)
        args->must_eat_num = ft_atoi(*argv);
    return(args);
}

t_philo *initialize(t_arg *args)
{
    t_philo *philos;
    int i;

    args = set_argv(args);
    philos = (t_philo *)malloc(sizeof(t_philo) * args->num_of_philo);
    if (!philos)
        ft_printerror("malloc failed");
    i = -1;
    while (++i < args->num_of_philo)
    {
        if (pthread_create(&(philos[i].philo_t), NULL, func, ) < 0)
            ft_printerror("Thread create error");
    }


}