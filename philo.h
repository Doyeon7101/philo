#ifndef PHILO_H
# define PHILO_H 

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

typedef enum e_status
{
    EATING,
    SLEEPING,
    THINKING
}   t_status;

typedef struct s_data
{
    int             num_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_num;
    pthread_mutex_t *forks;
}   t_data;

typedef struct s_philo
{
    pthread_t   philo_t;
    int         id;
    int         l;
    int         r;
    int         eat_cnt;
    int         remain_time;
    t_status    state;
} t_philo;

//utils
void ft_printerror(char *msg);
void	*ft_calloc(size_t cnt, size_t size);
void ft_atoi(int *dst, const char *str);

//init
void initialize(t_data *data, t_philo *philo, char **argv);

#endif