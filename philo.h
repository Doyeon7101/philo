#ifndef PHILO_H
# define PHILO_H 

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//input struct
typedef struct s_arg
{
    int num_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat_num;
}   t_arg;

typedef struct s_philo
{
    pthread_t philo_t;
    int id;
    int l;
    int r;
    int eat_cnt;
    int remain_time;
} t_philo;

//utils
void ft_printerror(char *msg);
int	ft_atoi(const char *str);

#endif