/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 13:38:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch_dead(void *arg)
{
	sem_wait(g_philo->corpse);
	g_philo->status = 0;
	return (arg);
}

void	report_corpse(int i)
{
	struct timeval	time;
	int				diff;
	int				time_i;
	int				time_p;

	gettimeofday(&time, NULL);
	time_i = get_timestamp(&time);
	time_p = get_timestamp(&g_philo->philo[i]->last_meal);
	diff = time_i - time_p;
	if (diff > g_philo->time_to_die)
	{
		sem_wait(g_philo->print);
		print_msg(i, MSG_DIED);
		g_philo->status = 0;
		g_philo->philo[i]->status = 0;
		sem_post(g_philo->corpse);
		sem_post(g_philo->print);
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
			g_philo->status = 0;
	}
	return (arg);
}

void	report_meal(int i)
{
	if (g_philo->nb_must_eat == -1)
		return ;
	if (g_philo->philo[i]->nb_meal < g_philo->nb_must_eat)
		return ;
	sem_wait(g_philo->print);
	g_philo->philo[i]->status = 0;
	print_msg(i, MSG_ENDED);
	g_philo->status = 0;
	sem_post(g_philo->meals);
	sem_post(g_philo->print);
}

void	make_philo(int i)
{
	if ((g_philo->philo[i]->pid = fork()) == -1)
		exit(ERR_INIT);
	if (g_philo->philo[i]->pid == 0)
	{
		pthread_create(&g_philo->philo[i]->monitor,
			NULL, philo_monitor, g_philo->philo[i]);
		pthread_detach(g_philo->philo[i]->monitor);
		while (g_philo->philo[i]->status)
		{
			report_meal(i);
			report_corpse(i);
		}
		exit(0);
	}
}
