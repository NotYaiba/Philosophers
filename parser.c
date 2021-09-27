#include "philosophers.h"

void init_data(t_data *data, char **av, int ac)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_todie = ft_atoi(av[2]);
    data->time_toeat = ft_atoi(av[3]);
    data->time_tosleep = ft_atoi(av[4]);
    data->meals = 0;
    if(ac == 6)
        data->meals = ft_atoi(av[5]);
}

int	check_args(char **av)
{
	int i;
	int j;

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

void log_data(t_data *data)
{
	printf("all philos : %d\n", data->num_philos);
	printf("time to die : %d\n", data->time_todie);
	printf("time to eat : %d\n", data->time_toeat);
	printf("time_tosleep : %d\n", data->time_tosleep);
	printf("meals : %d\n", data->meals);

	printf("---------------------------------------------\n");

	t_philo *tmp = data->philo;

	while (tmp)
	{
		printf("id : %d\n", (tmp)->id);
		tmp = tmp->next;
	}

	printf("---------------------------------------------\n");

	t_fork *tmp2 = data->fork;

	while (tmp2)
	{
		printf("id : %d\n", (tmp2)->philo);
		tmp2 = tmp2->next;
	}
}