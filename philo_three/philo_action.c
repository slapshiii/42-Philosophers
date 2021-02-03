/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:37:05 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:40:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_fork(int id)
{
	sem_wait(g_philo->lock);
	sem_wait(g_philo->forks);
	print_msg(id + 1, MSG_FORK);
	sem_wait(g_philo->forks);
	sem_post(g_philo->lock);
	print_msg(id + 1, MSG_FORK);
}

void	philo_eat(int id)
{
	print_msg(id + 1, MSG_EAT);
	usleep(g_philo->time_to_eat);
	gettimeofday(&(g_philo->last_meal[id]), NULL);
	g_philo->nb_meal[id]++;
	sem_post(g_philo->forks);
	sem_post(g_philo->forks);
}

void	philo_rest(int id)
{
	print_msg(id + 1, MSG_SLEEP);
	usleep(g_philo->time_to_sleep);
	print_msg(id + 1, MSG_THINK);
}