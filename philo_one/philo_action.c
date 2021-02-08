/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 16:12:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_philo(int i)
{
	t_data	*res;

	if (!(res = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	memset(res, 0, sizeof(t_data));
	res->id = i;
	res->status = 1;
	gettimeofday(&(res->last_meal), NULL);
	return (res);
}

void	*philo_monitor(void *arg)
{
	t_data	*philo;

	philo = arg;
	while (philo->status)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_rest(philo);
	}
	return (NULL);
}

void	philo_fork(t_data *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&g_philo->forks[philo->id]);
	else
		pthread_mutex_lock(&g_philo->forks[(philo->id + 1)
			% g_philo->nb_philo]);
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_FORK);
	pthread_mutex_unlock(g_philo->print);
	if (philo->id % 2)
		pthread_mutex_lock(&g_philo->forks[(philo->id + 1)
			% g_philo->nb_philo]);
	else
		pthread_mutex_lock(&g_philo->forks[philo->id]);
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_FORK);
	pthread_mutex_unlock(g_philo->print);
}

void	philo_eat(t_data *philo)
{
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_EAT);
	pthread_mutex_unlock(g_philo->print);
	gettimeofday(&(philo->last_meal), NULL);
	usleep(g_philo->time_to_eat);
	philo->nb_meal++;
	pthread_mutex_unlock(&g_philo->forks[philo->id]);
	pthread_mutex_unlock(&g_philo->forks[(philo->id + 1) % g_philo->nb_philo]);
}

void	philo_rest(t_data *philo)
{
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_SLEEP);
	pthread_mutex_unlock(g_philo->print);
	usleep(g_philo->time_to_sleep);
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_THINK);
	pthread_mutex_unlock(g_philo->print);
}
