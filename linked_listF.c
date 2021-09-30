#include "philosophers.h"

void	addback(t_philo **alst, t_philo *new)
{
	t_philo	*n;

	n = *alst;
	if (!new)
		return ;
	if (!*alst)
		(*alst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
}

void	add_front(t_philo **alst, t_philo *new)
{
	t_philo	*n;

	n = new;
	n->next = *alst;
	*alst = n;
}

t_philo	*new_philo(int content, t_data *data)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (new == NULL)
		return (NULL);
	new->id = content;
	new->status = 0;
	new->eatenmeals = 0;
	new->data = data;

	new->die = get_time();
	new->next = NULL;
	return (new);
}

t_fork	*new_fork(int content)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (new == NULL)
		return (NULL);
	new->philo = content;
	new->new_philo = 0;

	new->next = NULL;
	return (new);
}

void	addbackf(t_fork **alst, t_fork *new)
{
	t_fork	*n;

	n = *alst;
	if (!new)
		return ;
	if (!*alst)
		(*alst) = new;
	else
	{
		while (n->next)
			n = n->next;
		n->next = new;
	}
}

void	add_frontf(t_fork **alst, t_fork *new)
{
	t_fork	*n;

	n = new;
	n->next = *alst;
	*alst = n;
}