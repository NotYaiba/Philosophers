/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:54:54 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/11 15:35:03 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;
	long			i;

	gettimeofday(&time, NULL);
	i = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (i);
}

void	sleep_thread(int time)
{
	long	t;

	t = get_time();
	while (get_time() - t < time)
		usleep(50);
}

int	ready_to_eat(t_philo *philo)
{
	t_fork	*forkp;
	t_fork	*forks;

	forkp = get_fork(philo->data, philo->id);
	forks = forkp->next;
	pthread_mutex_lock(&forkp->flock);
	if (forkp->new_philo == 0)
	{
		print("has takken a fork\n", philo, get_time(), 1);
		forkp->new_philo = philo->id;
		philo->fork = forkp->philo;
	}
	pthread_mutex_unlock(&forkp->flock);
	pthread_mutex_lock(&forks->flock);
	if (forks->new_philo == 0)
	{
		print("has takken a fork\n", philo, get_time(), 1);
		forks->new_philo = philo->id;
		philo->fork1 = forks->philo;
	}
	pthread_mutex_unlock(&forks->flock);
	return (philo->fork && philo->fork1);
}

void	forks_down(t_philo *philo)
{
	t_fork	*forkp;
	t_fork	*forks;

	forkp = get_fork(philo->data, philo->id);
	forks = forkp->next;
	if (forkp->new_philo == 0)
		return ;
	if (forks->new_philo != 0)
	{
		forkp->new_philo = 0;
		forks->new_philo = 0;
		philo->fork1 = 0;
		philo->fork = 0;
		philo->status = 2;
		philo->eatenmeals++;
	}
}

t_fork	*get_fork(t_data *data, int philo_id)
{
	t_fork	*fork;

	fork = data->fork;
	while (fork)
	{
		if (fork->philo == philo_id)
			return (fork);
		fork = fork->next;
	}
	return (NULL);
}
