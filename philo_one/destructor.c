/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 16:12:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_mutex(void)
{
	int	i;

	if (g_philo->meals)
	{
		pthread_mutex_destroy(g_philo->meals);
		free(g_philo->meals);
	}
	if (g_philo->print)
	{
		pthread_mutex_destroy(g_philo->print);
		free(g_philo->print);
	}
	i = -1;
	if (g_philo->forks)
	{
		while (++i < g_philo->nb_philo)
			pthread_mutex_destroy(g_philo->forks + i);
		free(g_philo->forks);
	}
}

int			clean_exit(int status)
{
	int i;

	if (g_philo)
	{
		clean_mutex();
		i = -1;
		if (g_philo->philo)
		{
			while (++i < g_philo->nb_philo)
				free(g_philo->philo[i]);
			free(g_philo->philo);
		}
		free(g_philo);
	}
	g_philo = NULL;
	return (status);
}
