/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:28:13 by melkarmi          #+#    #+#             */
/*   Updated: 2021/07/12 22:54:44 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_philo
{
    int id;
}				t_philo;
typedef struct s_data
{
    int num_philos;
    int time_todie;
    int time_toeat;
    int time_tosleep;
    int meals_num;
    pthread_t *allphilo;
    pthread_mutex_t	*forks; 
}				t_data;

void ft_putstr(char *str, int fd);
int		ft_isdigit(int cc);
int ft_atoi(const char *s);
void init_data(t_data *data, char **av, int ac);
int	check_args(char **av);

#endif