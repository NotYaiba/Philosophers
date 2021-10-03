/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:55:05 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/03 16:55:07 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(char *msg, t_philo *philo, int time, int a)
{
	if (a != 3)
		pthread_mutex_lock(&philo->data->lock);
	if (a == 2)
	{
		write(2, msg, strlen(msg));
		exit(0);
	}
	else if (a == 1)
	{
		ft_putnbr_fd(time, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(philo->id, 1);
		ft_putchar_fd(' ', 1);
		write(1, msg, strlen(msg));
	}
	if (msg[0] != 'd')
		pthread_mutex_unlock(&philo->data->lock);
}

void	ft_putchar_fd(char c, int i)
{
	write(i, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	i;

	i = n;
	if (i < 0)
	{
		i = -i;
		ft_putchar_fd(45, fd);
	}
	if (i > 9)
	{
		ft_putnbr_fd(i / 10, fd);
		ft_putchar_fd(i % 10 + 48, fd);
	}
	if (i <= 9 && i >= 0)
	{
		ft_putchar_fd(i + 48, fd);
	}
}

int	log_error(char *err, int ret)
{
	ft_putstr(err, 2);
	return (ret);
}
