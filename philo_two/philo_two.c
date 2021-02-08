/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 14:33:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch_dead(void *arg)
{
	sem_wait(g_philo->corpse);
	g_philo->status = 0;
	return (arg);
}

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
		sem_wait(g_philo->print);
		print_msg(philo->id, MSG_DIED);
		g_philo->status = 0;
		sem_post(g_philo->print);
		sem_post(g_philo->corpse);
		philo->status = 0;
	}
}

void	*watch_meal(void *arg)
{
	int	eaten;

	eaten = 0;
	while (g_philo->status)
	{
		sem_wait(g_philo->meals);
		eaten++;
		if (eaten == g_philo->nb_philo)
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
	sem_wait(g_philo->print);
	print_msg(philo->id, MSG_ENDED);
	sem_post(g_philo->print);
	sem_post(g_philo->meals);
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
