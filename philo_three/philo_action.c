/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 16:42:54 by user42           ###   ########.fr       */
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
	sem_wait(g_philo->lock);
	sem_wait(g_philo->forks);
	print_msg(philo->id, MSG_FORK);
	sem_wait(g_philo->forks);
	sem_post(g_philo->lock);
	print_msg(philo->id, MSG_FORK);
}

void	philo_eat(t_data *philo)
{
	print_msg(philo->id, MSG_EAT);
	gettimeofday(&(philo->last_meal), NULL);
	usleep(g_philo->time_to_eat);
	philo->nb_meal++;
	sem_post(g_philo->forks);
	sem_post(g_philo->forks);
}

void	philo_rest(t_data *philo)
{
	print_msg(philo->id, MSG_SLEEP);
	usleep(g_philo->time_to_sleep);
	print_msg(philo->id, MSG_THINK);
}