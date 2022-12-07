#include "philo.h"

bool    pickup(t_philo *philo, t_data *data)
{
    if(!pthread_mutex_lock(&data->forks[philo->l]) || \
        !pthread_mutex_lock(&data->forks[philo->r]))
        // 실패@!;;
        return(false);
    return(true) ;
}

bool    putdown(t_philo *philo, t_data *data)
{
    if(!pthread_mutex_unlock(&data->forks[philo->l]) || \
        !pthread_mutex_unlock(&data->forks[philo->r]))
        return(false);
    return(true);
}

bool    sleep(t_philo *philo)
{
    //timestamp

}

bool    eating(t_philo *philo, t_data *data)
{
    long long cur;

    if (!get_timestamp(&cur)) // timestamp 어케할지좀...
        return(false);
    if (!pickup(philo, data))
        return (false);
    print_status(EATING, philo->id, data->time);
    wait_intaval();
    if (!putdown(philo, data))
}

bool    thinking(t_philo *philo)
{

}

