/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 14:36:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *g_philo;

void	make_philo(int i)
{
	pthread_create(&g_philo->philo[i]->monitor,
		NULL, philo_monitor, g_philo->philo[i]);
	pthread_create(&g_philo->philo[i]->main,
		NULL, watcher_loop, g_philo->philo[i]);
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
	sem_post(g_philo->forks);
	sem_post(g_philo->forks);
	while (i < g_philo->nb_philo)
	{
		pthread_join(g_philo->philo[i]->monitor, NULL);
		pthread_join(g_philo->philo[i]->main, NULL);
		sem_post(g_philo->meals);
		i++;
	}
	sem_post(g_philo->corpse);
	pthread_join(monitor_meal, NULL);
	pthread_join(monitor_dead, NULL);
}

/*
**	nb_philo; time_to_die; time_to_eat; time_to_sleep; nb_must_eat
*/

int		main(int ac, char **av)
{
	int				status;
	int				i;

	status = 0;
	i = 0;
	if (ac < 5 || ac > 6)
		return (ERR_NUM_ARG);
	if ((status = get_param(av)))
	{
		fprintf(stderr, "An error has occured\n");
		return (clean_exit(status));
	}
	launch_thread();
	return (clean_exit(status));
}
