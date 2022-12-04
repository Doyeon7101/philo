#include "philo.h"
void ft_printerror(char *msg)
{
    printf("ERROR ! : %s", msg);
    exit(EXIT_FAILURE);
}

void ft_atoi(int *dst, const char *str)
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
	*dst = r * i;
	return ;
}

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*ret;
	int		n;
	void	*ptr;

	ret = (void *)malloc(size * cnt);
	n = cnt * size;
	ptr = ret;
	if (!ret)
		return (NULL);
	while (n-- > 0)
	{
		*(char *)ptr = 0;
		++ptr;
	}
	return (ret);
}