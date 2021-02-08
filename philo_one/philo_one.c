/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 16:07:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_corpse(t_data *philo)
{
	struct timeval	time;
	int				diff;
	int				time_i;
	int				time_p;

	gettimeofday(&time, NULL);
	time_i = get_timestamp(&time);
	time_p = get_timestamp(&philo->last_meal);
	diff = time_i - time_p;
	if (diff > g_philo->time_to_die)
	{
		pthread_mutex_lock(g_philo->print);
		print_msg(philo->id, MSG_DIED);
		g_philo->status = 0;
		pthread_mutex_unlock(g_philo->print);
		philo->status = 0;
	}
}

void	*watch_meal(void *arg)
{
	int	eaten;

	eaten = 0;
	while (g_philo->status)
	{
		if (g_philo->finished == g_philo->nb_philo)
			break ;
	}
	g_philo->status = 0;
	return (arg);
}

void	report_meal(t_data *philo)
{
	if (g_philo->nb_must_eat == -1)
		return ;
	if (philo->nb_meal < g_philo->nb_must_eat)
		return ;
	pthread_mutex_lock(g_philo->print);
	print_msg(philo->id, MSG_ENDED);
	pthread_mutex_unlock(g_philo->print);
	pthread_mutex_lock(g_philo->meals);
	g_philo->finished++;
	pthread_mutex_unlock(g_philo->meals);
	philo->status = 0;
}

void	*watcher_loop(void *arg)
{
	t_data	*philo;

	philo = arg;
	while (philo->status)
	{
		report_meal(philo);
		report_corpse(philo);
	}
	return (NULL);
}
