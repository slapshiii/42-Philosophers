/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 12:32:55 by user42           ###   ########.fr       */
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

	i = 0;
	g_philo->status = 1;
	while (i < g_philo->nb_philo)
		make_philo(i++);
	while (g_philo->status)
		;
	i = 0;
	while (i < g_philo->nb_philo)
	{
		g_philo->philo[i]->status = 0;
		pthread_join(g_philo->philo[i]->monitor, NULL);
		pthread_join(g_philo->philo[i]->main, NULL);
		i++;
	}
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
