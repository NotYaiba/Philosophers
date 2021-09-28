/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:28:13 by melkarmi          #+#    #+#             */
/*   Updated: 2021/09/27 22:44:13 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sys/time.h>



typedef struct s_fork
{
	int				philo;
	int				new_philo;
	pthread_mutex_t flock;
	struct s_fork	*next;


}				t_fork;
typedef struct s_data
{
    int num_philos;
    int time_todie;
    int time_toeat;
    int time_tosleep;
    int meals;
	int philo_id;
    pthread_mutex_t lock;
	t_fork			*fork;

}				t_data;
typedef struct s_philo
{
    int id;
	int status;
	int eatenmeals;
	int	die;
	pthread_t 		trd_id;
	t_data			*data;
	struct s_philo *next;
}				t_philo;

void ft_putstr(char *str, int fd);
void log_data(t_data *data);
int		ft_isdigit(int cc);
int ft_atoi(const char *s);
void init_data(t_data *data, char **av, int ac);
int	check_args(char **av);
// linked list functions

t_philo	*new_philo(int content, t_data *data);
t_fork	*new_fork(int content);

void	add_front(t_philo **alst, t_philo *new);
void	addback(t_philo **alst, t_philo *new);
void	add_frontf(t_fork **alst, t_fork *new);
void	addbackf(t_fork **alst, t_fork *new);

//log
void print(char *msg, t_philo *philo , int time, int a, t_data *data);
void			ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int i);
// utils
int	get_time(void);

#endif