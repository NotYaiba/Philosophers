/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melkarmi <melkarmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:29:02 by melkarmi          #+#    #+#             */
/*   Updated: 2021/07/10 19:55:30 by melkarmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_putstr(char *str, int fd)
{
    int i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void    *routine(void *i)
{
    int a = *((int *) i);
	t_philo *philos = (t_philo *)i;
    
    printf("%d is eating\n", philos->idd);                                                                                                                                                                                                            
	ft_putstr("hello\n", 1);
     printf("%d is done eating \n", a);
    return (NULL);
}
int main(int ac, char **av)
{
    pthread_t *th;
    pthread_mutex_t *fork;
    t_philo *philos;
    t_data *data;

    philos = malloc(sizeof(t_philo));
    data = malloc(sizeof(t_data));
    int i;
    int d = 5;
    th = malloc(sizeof(pthread_t) * d);
    philos->fork= malloc(sizeof(pthread_mutex_t) * d);
    philos->id= malloc(sizeof(pthread_mutex_t) * d);
    i = 0;
    while (i < d)
    {
        pthread_mutex_init(&philos->fork[i],NULL);
        philos->id[i] = i + 1;
        i++;
    }
    i = 0;
    while (i < d)
    {
        pthread_create(&th[i], NULL, &routine, philos);
        i++;
    }
    i = 0;
        
    while (1);
    i = 0;
    while (i < d)
    {
        pthread_mutex_destroy(&philos->fork[i]);
        i++;
    }
    return (0);
}

