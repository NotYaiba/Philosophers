/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/09/27 03:27:25 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	logError(char *err, int ret)
{
	ft_putstr(err, 2);
	return (ret);
}

void	*routine(void *tmp)
{
	t_data *data;
	data = (t_data*)tmp;
	printf("dkheeel %d\n", data->philo_id);
	
	// while(1)
	// {
		
	// }
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

void start_sum(t_data *data)
{
	t_philo *philo;
	t_fork 	*fork;
	philo = data->philo;
	while (philo)
	{
		if (philo->id % 2 == 1 &&  philo->id != data->num_philos)
		{
			fork = get_fork(data ,philo->id);
			fork->new_philo = philo->id;
			fork = get_fork(data ,philo->id + 1);
			fork->new_philo = philo->id;
			philo->status = 1;
			print("has takken fork\n", philo, get_time(), 1);
			print("has takken fork\n", philo, get_time(), 1);
			// usleep(900);
		}
		else
		{
			philo->status = 0;
		}
		pthread_mutex_lock(&data->lock);

		data->philo_id = philo->id;
		
		printf("%d\n", data->philo_id);
		// pthread_create(&philo->trd_id, NULL, &routine, data);
		pthread_mutex_unlock(&data->lock);

		philo = philo->next;
	}
}

int main(int ac, char **av)
{
    t_data *data;
	data = malloc(sizeof(t_data));
	data->philo = NULL;
	
	if (ac < 5 || ac > 6 || check_args(av) == 0)
		return (logError("Error.\n", 0));
	data = malloc(sizeof(t_data));
	init_data(data, av, ac);
	int i;

	i = 1;
	while (i <= data->num_philos)
	{
		///init philos and forks
		addback(&data->philo, new_philo(i));
		addbackf(&data->fork, new_fork(i));\
		if (pthread_mutex_init(&data->fork->flock, NULL) != 0)
			print("\n mutex init failed\n", NULL, 0, 2);
		////
		if (pthread_mutex_init(&data->lock, NULL) != 0)
			print("\n mutex init failed\n", NULL, 0, 2);
		// pthread_create(&(tid[i]), NULL, &routine, NULL);
		i++;
	}
	start_sum(data);
	// log_data(data);
	// while (1);
    return (0);
}

