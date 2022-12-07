#include "philo.h"
/**
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
**/

bool    get_timestamp(long long *ret)
{
    struct timeval t;

    if (!gettimeofday(&t, NULL))
        return(false);
    *ret = (t.tv_sec * MILLI) + (t.tv_usec / MILLI);
    return (true);
}

bool    print_status(t_status status, int id, long long start)
{
    long long intaval;
    long long cur;

    if (!get_timestamp(&cur))
        return(false);
    intaval = cur - start;
    if (status == PICKUP)
        printf("%lld %d has taken a fork", intaval, id);
    if (status == EATING)
        printf("%lld %d is eating", intaval, id);
    if (status == SLEEPING)
        printf("%lld %d is sleeping", intaval, id);
    if (status == THINKING)
        printf("%lld %d is thinking", intaval, id);
    if (status == DIED)
        printf("%lld %d died", intaval, id);
    return (true);
}
