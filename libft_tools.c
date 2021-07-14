#include "philosophers.h"

int		ft_isdigit(int cc)
{
	if (cc >= 48 && cc <= 57)
		return (1);
	return (0);
}

void ft_putstr(char *str, int fd)
{
    int i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int ft_atoi(const char *s)
{
	char	*str;
	int		x;
	int		n;

	str = (char *)s;
	x = 0;
	n = 1;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' ||
		*str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	if (*str == '-')
		n = -1;
	if (*str == '-' || *str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		if (x < 0 && n < 0)
			return (0);
		if (x < 0 && n > 0)
			return (-1);
		x = x * 10 + (*str - 48);
		str++;
	}
	return (x * n);
}