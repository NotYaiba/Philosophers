/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaiba <yaiba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:28:13 by melkarmi          #+#    #+#             */
/*   Updated: 2021/10/19 02:36:35 by yaiba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				philo;
	int				new_philo;
	pthread_mutex_t	flock;
	struct s_fork	*next;
}				t_fork;

typedef struct s_data
{
	int				num_philos;
	int				time_todie;
	int				time_toeat;
	int				time_tosleep;
	int				meals;
	int				philo_id;
	pthread_mutex_t	lock;
	pthread_mutex_t	alive;
	t_fork			*fork;
	int				run;
	long			start_time;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				status;
	int				eatenmeals;
	long			die;
	int				fork;
	int				fork1;
	pthread_t		trd_id;
	t_data			*data;
	struct s_philo	*next;
}				t_philo;

void	check_isalive(t_philo *philo);
void	ft_putstr(char *str, int fd);
int		ft_strlen(char *str);
void	log_data(t_philo *philo);
int		ft_isdigit(int cc);
int		ft_atoi(const char *s);
void	init_data(t_data *data, char **av, int ac);
void	init_mutex(t_data *data);
int		check_args(char **av);
t_philo	*create_philos(t_philo *philo, t_data *data);
t_philo	*new_philo(int content, t_data *data);
t_fork	*new_fork(int content);
void	addback(t_philo **alst, t_philo *new);
void	addbackf(t_fork **alst, t_fork *new);
void	print(char *msg, t_philo *philo, long time, int a);
void	ft_putnbr_fd(long n, int fd);
void	ft_putchar_fd(char c, int i);
int		log_error(char *err, int ret);
long	get_time(void);
void	sleep_thread(int time, t_philo *philo);
t_fork	*get_fork(t_data *data, int philo_id);
int		ready_to_eat(t_philo *philo);
void	forks_down(t_philo *philo);
t_fork	*get_fork(t_data *data, int philo_id);
void	start_threads(t_philo *philos);
void	*routine(void *tmp);
void	free_all(t_philo **philo);
void	log_died(t_philo *philo, t_data	*data);
int		check_errors(int ac, char **av);

#endif