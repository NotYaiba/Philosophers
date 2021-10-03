/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/03 17:04:42 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_isalive(t_philo *philo)
{
	if (get_time() - philo->die >= philo->data->time_todie)
	{
		print("died\n", philo, get_time(), 1);
		exit(0);
	}
	if (philo->eatenmeals == philo->data->meals)
		exit(0);
}

void	update(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	check_isalive(philo);
	if (philo->status == 0 || philo->status == 3)
		philo->status = ready_to_eat(philo);
	else if (philo->status == 1)
		forks_down(philo);
	else if (philo->status == 2)
		philo->status = 3;
}

void	*routine(void *tmp)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)tmp;
	data = philo->data;
	while (1)
	{
		if (philo->status == 1)
		{
			print("is eating\n", philo, get_time(), 1);
			philo->die = get_time();
			sleep_thread(data->time_toeat);
			print("is done eating\n", philo, get_time(), 1);
		}
		else if (philo->status == 2)
		{
			print("is sleeping\n", philo, get_time(), 1);
			sleep_thread(data->time_tosleep);
		}
		else if (philo->status == 3)
			print("is thinking\n", philo, get_time(), 1);
		update(philo);
	}
	return (NULL);
}

void	start_sum(t_philo *philos)
{
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	i = 1;
	philo = philos;
	while (i <= philos->data->num_philos)
	{
		if (philo->id % 2 == 1 && philo->id != philo->data->num_philos)
		{
			fork = get_fork(philo->data, philo->id);
			fork->new_philo = philo->id;
			fork = fork->next;
			fork->new_philo = philo->next->id;
			philo->status = 1;
			print("has takken1 fork\n", philo, get_time(), 1);
			print("has takken1 fork\n", philo, get_time(), 1);
		}
		else
			philo->status = 0;
		i++;
		philo = philo->next;
	}
	start_threads(philos);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	*philo;
	t_fork	*headf;
	int		i;

	philo = NULL;
	if (ac < 5 || ac > 6 || check_args(av) == 0)
		return (log_error("Error.\n", 0));
	data = malloc(sizeof(t_data));
	init_data(data, av, ac);
	init_mutex(data);
	headf = data->fork;
	while (headf->next)
		headf = headf->next;
	headf->next = data->fork;
	philo = create_philos(philo, data);
	// start_sum(philo);
	while (1)
	{
	}
	return (0);
}
