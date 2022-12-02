#include "philo.h"
int main(int argc, char **argv)
{
    t_arg args;
    t_philo *philo;

    if (argc != 5 || argc != 6)
        ft_printerror("argc errer");
    args = set_argv(*argv);
    philo = initialize(*argv);
}
