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
// void log_data(t_philo *philo)
// {
// 	int i = 0;
// 	t_fork *tmp = philo->data->fork;

// 	while (tmp)
// 	{
// 		printf("id : %d\n", (tmp)->philo);
// 		tmp = tmp->next;

// 		if (i == philo->data->num_philos - 1)
// 			break ;
// 		i++;
// 	}
// }