#include "philosophers.h"


int	get_time(void)
{
	struct timeval	time;
	unsigned int	i;

	gettimeofday(&time, NULL);
	i = (unsigned int)time.tv_sec;
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	sleep_thread(int time)
{
	int t;

	t = get_time();
	while (get_time() - t < time)
		usleep(50);
}

int	ready_to_eat(t_philo *philo)
{
	t_fork *forkp;
	t_fork *forks;


	forkp = get_fork(philo->data , philo->id);
	forks = forkp->next;
	printf("fork id is %d\n", forkp->philo);
	printf("next fork id is %d\n", forks->philo);
	pthread_mutex_lock(&forkp->flock);
	if (forkp->new_philo == 0)
	{
		print("has takken a fork\n", philo , get_time(), 1, philo->data);
		forkp->new_philo = philo->id;
	}
	else
	{
			return (0);
	}
	


	pthread_mutex_unlock(&forkp->flock);
	pthread_mutex_lock(&forks->flock);
	if (forks->new_philo == 0)
	{
		print("has takken a fork\n", philo , get_time(), 1, philo->data);
		forks->new_philo = philo->id;
	}
	else
	{
		return (0);
	}
	
	pthread_mutex_unlock(&forks->flock);
	return(1);
}

void	forks_down(t_philo * philo)
{
	t_fork	*forkp;
	t_fork	*forks;

	forkp = get_fork(philo->data , philo->id);
	forks = forkp->next;
	if (forkp->new_philo == 0)
		return ;
	if (forks->new_philo != 0)
	{
		forkp->new_philo = 0;
		forks->new_philo = 0;
	}
	philo->status = 2; //sleep
	philo->eatenmeals++; //sleep

}