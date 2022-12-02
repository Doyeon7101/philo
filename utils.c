#include "philo.h"
void ft_printerror(char *msg)
{
    printf("ERROR ! : %s", msg);
    exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	long	r;
	int		i;

	r = 0;
	i = 1;
	while (*str == ' ' || *str == '\t' || *str == '\r' \
		|| *str == '\n' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		r *= 10;
		r += *str - 48;
		str++;
	}
	return (r * i);
}
