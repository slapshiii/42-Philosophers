/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 15:56:28 by user42           ###   ########.fr       */
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
		if (philo->status)
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
	print_msg(philo->id, MSG_FORK);
	if (philo->id % 2)
		pthread_mutex_lock(&g_philo->forks[(philo->id + 1)
			% g_philo->nb_philo]);
	else
		pthread_mutex_lock(&g_philo->forks[philo->id]);
	print_msg(philo->id, MSG_FORK);
}

void	philo_eat(t_data *philo)
{
	philo->nb_meal++;
	philo->is_eating = 1;
	print_msg(philo->id, MSG_EAT);
	if (philo->nb_meal == g_philo->nb_must_eat
		&& g_philo->nb_must_eat != -1)
	{
		philo->status = 0;
		print_msg(philo->id, MSG_ENDED);
		g_philo->finished++;
	}
	usleep(g_philo->time_to_eat * 1000);
	gettimeofday(&(philo->last_meal), NULL);
	philo->is_eating = 0;
	pthread_mutex_unlock(&g_philo->forks[philo->id]);
	pthread_mutex_unlock(&g_philo->forks[(philo->id + 1) % g_philo->nb_philo]);
}

void	philo_rest(t_data *philo)
{
	print_msg(philo->id, MSG_SLEEP);
	usleep(g_philo->time_to_sleep * 1000);
	print_msg(philo->id, MSG_THINK);
}
