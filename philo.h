#ifndef PHILO_H
# define PHILO_H 

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

# define EPSILON	10
# define MILLI		1000

typedef enum e_vaild
{
    INVAILD,
    VAILD
} t_vaild;

typedef enum e_status
{
    PICKUP,
    EATING,
    PUTDOWN,
    SLEEPING,
    THINKING,
    DIED
}   t_status;

typedef struct s_data
{
    int             num_of_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat_num;
    long long       time;
    pthread_mutex_t *forks;
    pthread_mutex_t *print;
    pthread_mutex_t *dining;
}   t_data;

typedef struct s_philo
{
    pthread_t   philo_t;
    int         id;
    int         l;
    int         r;
    int         eat_cnt;
    int         remain_time;
    long long   cur;
    t_data      *data;
} t_philo;

//utils
void	*ft_calloc(size_t cnt, size_t size);
bool bool_atoi(int *dst, const char *str);

//init
bool initialize(t_data *data, t_philo *philo, char **argv);

void routine(void *arg);

// print.c
bool    print_status(t_status status, int id, long long start);
bool    get_timestamp(long long *ret);
#endif