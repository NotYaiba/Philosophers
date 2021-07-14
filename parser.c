#include "philosophers.h"

void init_data(t_data *data, char **av, int ac)
{
    data->num_philos = ft_atoi(av[1]);
    data->time_todie = ft_atoi(av[2]);
    data->time_toeat = ft_atoi(av[3]);
    data->time_tosleep = ft_atoi(av[4]);
    data->meals_num = 0;
    if(ac == 6)
        data->meals_num = ft_atoi(av[5]);
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