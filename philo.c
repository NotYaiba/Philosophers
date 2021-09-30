/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/09/30 04:26:41 by yaiba            ###   ########.fr       */
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
void	check_isalive(t_philo *philo)
{
	if(get_time() - philo->die >= philo->data->time_todie)
	{
		print("died\n", philo , get_time(), 1, philo->data);
		exit(0);
	}
}

void	update(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	check_isalive(philo);
	if (philo->status == 0 || philo->status == 3)
		philo->status = ready_to_eat(philo);
	else if (philo->status == 1)
		forks_down(philo);
	else if(philo->status == 2)
		philo->status = 3;
}

void	*routine(void *tmp)
{	

	t_philo *philo;
	t_data *data;

	philo = (t_philo*)tmp;
	data = philo->data;
	pthread_mutex_lock(&data->lock);
	// printf("---dkheeel salam %d----\n", pid);	
	pthread_mutex_unlock(&data->lock);
	while(1)
	{
		if (philo->status == 1)
		{
			print("is eating\n", philo, get_time(), 1 , data);
			philo->die = get_time();
			sleep_thread(data->time_toeat);
			print("is done sleping\n", philo, get_time(), 1 , data);
			
		}
		else if(philo->status == 2)
		{
			print("is sleeping\n", philo, get_time(), 1 , data);
			sleep_thread(data->time_tosleep);
		}
		else if (philo->status == 3)
			print("is thinking\n", philo, get_time(), 1 , data);
		update(philo);
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
	int i;

	i = 0;
	philo = philos;
	while (philo)
	{
		if (philo->id % 2 == 1 &&  philo->id != philo->data->num_philos)
		{
			fork = get_fork(philo->data ,philo->id);
			fork->new_philo = philo->id;
			fork = fork->next;
			fork->new_philo = philo->id;
			philo->status = 1;
			print("has takken fork\n", philo, get_time(), 1, philo->data);
			print("has takken fork\n", philo, get_time(), 1, philo->data);
		}
		else
		{
			philo->status = 0;
		}
		pthread_create(&(philo->trd_id), NULL, &routine, philo);

		if (i == philo->data->num_philos - 1)
			break;
		i++;
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
	t_philo	*head;
	head = philo;
	while (head->next)
		head = head->next;
	head->next = philo;
	
	start_sum(philo);
	// log_data(philo);
	while (1){

	}
    return (0);
}

