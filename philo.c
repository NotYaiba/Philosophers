/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/11 17:18:45 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_isalive(t_philo *philo)
{
	t_philo	*phi;

	phi = philo;
	if (get_time() - philo->die >= (long)philo->data->time_todie)
	{
		if (philo->status == 1)
			return (0);
		log_died(philo, philo->data);
		return (1);

	}
	// if (philo->data->meals != -1)
	// {
	// 	pthread_mutex_lock(&philo->data->lock);
	// 	while (phi)
	// 	{
	// 		if (phi->eatenmeals < philo->data->meals)
	// 		{
	// 			pthread_mutex_unlock(&philo->data->lock);
	// 			return 0;
	// 		}
	// 		if (phi->id == philo->data->num_philos)
	// 			break ;
	// 		phi = phi->next;
	// 	}
	// 	// philo->data->run = 0;
	// }
	return (0);
}

void	update(t_philo *philo)
{
	t_data	*data;

	data = philo->data;

	if (philo->status == 0 || philo->status == 3)
		philo->status = ready_to_eat(philo);
	else if (philo->status == 1)
		forks_down(philo);
	else if (philo->status == 2)
		philo->status = 3;

} 

int	super_visoir(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	while (1)
	{
		if (check_isalive(philo) == 1)
		{
			return (0);
		}
		philo = philo->next;
	}
	return (0);
} 
void	*routine(void *tmp)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)tmp;
	data = philo->data;
	while (data->run)
	{
		usleep(10);
		if (philo->status == 1)
		{
			print("is eating\n", philo, get_time(), 1);
			sleep_thread(data->time_toeat);
			philo->die = get_time();
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
			print("has takken fork\n", philo, get_time(), 1);
			print("has takken fork\n", philo, get_time(), 1);
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
	start_sum(philo);
	super_visoir(philo);
	free_all(&philo);
	return (0);
}
