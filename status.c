#include "philo.h"
void    sleep(t_philo *philo)
{

}
void    eating(t_philo *philo)
{

}
void    thinking(t_philo *philo)
{

}

void    pickup(t_philo *philo)
{

}

void    putdown(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->forks[philo->l]);
    pthread_mutex_lock(&philo->data->forks[philo->r]);
    philo->state = THINKING;
    
    pthread_mutex_unlock(&philo->data->forks[philo->l]);
    pthread_mutex_unlock(&philo->data->forks[philo->r]);

}
