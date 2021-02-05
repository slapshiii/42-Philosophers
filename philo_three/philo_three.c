/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 18:17:08 by user42           ###   ########.fr       */
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
	int 			time_p;

	gettimeofday(&time, NULL);
	time_i = get_timestamp(&time);
	time_p = get_timestamp(&g_philo->philo[i]->last_meal); 
	diff = time_i - time_p;
	if (diff > g_philo->time_to_die)
	{
		sem_wait(g_philo->print);
		print_msg(i, MSG_DIED);
		g_philo->status = 0;
		//sem_post(g_philo->print);
		sem_post(g_philo->corpse);
		g_philo->philo[i]->status = 0;
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
			break;
	}
	g_philo->status = 0;
	return (arg);
}

void	report_meal(int i)
{
	if (g_philo->nb_must_eat == -1)
		return;
	if (g_philo->philo[i]->nb_meal < g_philo->nb_must_eat)
		return;
	sem_wait(g_philo->print);
	print_msg(i, MSG_ENDED);
	sem_post(g_philo->print);
	sem_post(g_philo->meals);
	g_philo->philo[i]->status = 0;
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

void	launch_thread(void)
{
	int			i;
	pthread_t	monitor_dead;
	pthread_t	monitor_meal;

	i = 0;
	g_philo->status = 1;
	while (i < g_philo->nb_philo)
		make_philo(i++);
	pthread_create(&monitor_dead, NULL, watch_dead, NULL);
	pthread_create(&monitor_meal, NULL, watch_meal, NULL);
	while (g_philo->status)
		;
	i = 0;
	while (i < g_philo->nb_philo)
	{
		kill(g_philo->philo[i]->pid, SIGKILL);
		sem_post(g_philo->meals);
		i++;
	}
	sem_post(g_philo->corpse);
	pthread_join(monitor_meal, NULL);
	pthread_join(monitor_dead, NULL);
}