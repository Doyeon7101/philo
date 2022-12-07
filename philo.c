#include "philo.h"
/**
int terminate(t_vaild status, t_data *data)
{
}
**/

int main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;

    if (argc != 5 && argc != 6)
        return(terminate(INVAILD, &data));
    if (!initialize(&data, philo, argv));
        return(terminate(INVAILD, &data));
    if (!routine(&data, philo))
        return(terminate(INVAILD, &data));
}
