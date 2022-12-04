#include "philo.h"
int main(int argc, char **argv)
{
    t_data data;
    t_philo *philo;

    if (argc != 5 && argc != 6 )
        ft_printerror("argc error");
    initialize(&data, philo, argv);
}
