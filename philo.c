/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/09/28 16:26:25 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	logError(char *err, int ret)
{
	ft_putstr(err, 2);
	return (ret);
}

// t_philo *get_philo(int philo_id, t_data *data)
// {
// 	t_philo *philos;

// 	philos = data->philo;
// 	while(philos)
// 	{
// 		if (philos->id == philo_id)
// 			return (philos);
// 		philos = philos->next;
// 	}
// 	return (NULL);
// }

void	*routine(void *tmp)
{	

	t_philo *philo;

	philo = (t_philo*)tmp;
	
	pthread_mutex_lock(&philo->data->lock);
	printf("---dkheeel salam %d----\n", philo->id);	
	pthread_mutex_unlock(&philo->data->lock);
 
	while(1)
	{
			
	}
	return(NULL);
}

t_fork	*get_fork(t_data *data , int philo_id)
{
	t_fork *fork;
	fork =	data->fork;
	while (fork)
	{
		if (fork->philo == philo_id)
			return (fork);
		fork = fork->next;
	}
	return (NULL);
}

void start_sum(t_philo *philos)
{
	t_philo *philo;
	t_fork 	*fork;
	philo = philos;
	while (philo)
	{
		printf("id : %d\n", philo->id);
		if (philo->id % 2 == 1 &&  philo->id != philo->data->num_philos)
		{
			fork = get_fork(philo->data ,philo->id);
			fork->new_philo = philo->id;
			fork = get_fork(philo->data ,philo->id + 1);
			fork->new_philo = philo->id;
			philo->status = 1;
			print("has takken fork\n", philo, get_time(), 1, philo->data);
			print("has takken fork\n", philo, get_time(), 1, philo->data);
			usleep(900);
		}
		else
		{
			philo->status = 0;
		}
		philo = philo->next;
	}
	philo = philos;
	while (philo)
	{
		
		pthread_create(&(philo->trd_id), NULL, &routine, philo);
		// usleep(20200);
		philo = philo->next;
	}

}

int main(int ac, char **av)
{
    t_data *data;
    t_philo *philo;

	philo = NULL;
	data = malloc(sizeof(t_data));
	if (ac < 5 || ac > 6 || check_args(av) == 0)
		return (logError("Error.\n", 0)); 
	init_data(data, av, ac);
	int i;

	i = 1;
	data->fork = NULL;
	while (i <= data->num_philos)
	{
		///init philos and forks
		addbackf(&data->fork, new_fork(i));
		if (pthread_mutex_init(&data->fork->flock, NULL) != 0)
			print("\n mutex init failed\n", NULL, 0, 2, data);
		// ////
		if (pthread_mutex_init(&data->lock, NULL) != 0)
			print("\n mutex init failed\n", NULL, 0, 2, data);

		i++;
	}
	i = 1;
	while (i <= data->num_philos)
	{
		addback(&philo, new_philo(i, data));
		i++;
	}

	start_sum(philo);
	// log_data(data);
	while (1){

	}
    return (0);
}

