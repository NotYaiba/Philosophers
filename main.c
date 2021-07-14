/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/07/12 22:38:06 by yaiba            ###   ########.fr       */
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
	t_philo *philo;
	philo = tmp;
	
	printf("%d entering\n", philo->id);
}


void	start_sum(t_data *data, t_philo **philo)
{
	int i;
	i = 0;
	printf("%d\n", data->num_philos);
	// return ;
	while (i < data->num_philos)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i;
		pthread_create(&data->allphilo[i], NULL, (void *)routine, philo[i]);
		i++;
	}

}

int main(int ac, char **av)
{
    t_data *data;
	t_philo	**philo;

	if (ac < 5 || ac > 6 || check_args(av) == 0)
		return (logError("Error.\n", 0));
	philo = malloc(sizeof(t_philo*) * data->num_philos);
	data = malloc(sizeof(t_data));
	data->allphilo = malloc(sizeof(pthread_t) * data->num_philos);
	
	init_data(data, av, ac);
	start_sum(data, philo);
	while (1);
    return (0);
}

