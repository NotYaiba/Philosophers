/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:54:37 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/03 17:04:02 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, char **av, int ac)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_todie = ft_atoi(av[2]);
	data->time_toeat = ft_atoi(av[3]);
	data->time_tosleep = ft_atoi(av[4]);
	data->meals = 0;
	data->philo_id = 0;
	if (ac == 6)
		data->meals = ft_atoi(av[5]);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 1;
	data->fork = NULL;
	while (i <= data->num_philos)
	{
		addbackf(&data->fork, new_fork(i));
		if (pthread_mutex_init(&data->fork->flock, NULL) != 0)
			print("\n mutex init failed\n", NULL, 0, 2);
		i++;
	}
	if (pthread_mutex_init(&data->lock, NULL) != 0)
		print("\n mutex init failed\n", NULL, 0, 2);
}

t_philo	*create_philos(t_philo *philo, t_data *data)
{
	t_philo	*head;
	int		i;

	i = 1;
	while (i <= data->num_philos)
	{
		addback(&philo, new_philo(i, data));
		i++;
	}
	head = philo;
	while (head->next)
		head = head->next;
	head->next = philo;
	return (philo);
}

void	start_threads(t_philo *philos)
{
	int		i;
	t_philo	*philo;

	philo = philos;
	i = 1;
	while (i <= philos->data->num_philos)
	{
		pthread_create(&(philo->trd_id), NULL, &routine, philo);
		i++;
		philo = philo->next;
	}
}
