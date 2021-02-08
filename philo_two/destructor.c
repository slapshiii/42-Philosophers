/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 12:51:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_exit(int status)
{
	int i;

	i = -1;
	if (g_philo)
	{
		sem_unlink(SEM_LOCK);
		sem_unlink(SEM_FORK);
		sem_unlink(SEM_MEAL);
		sem_unlink(SEM_DEAD);
		sem_unlink(SEM_MSGS);
		sem_close(g_philo->lock);
		sem_close(g_philo->forks);
		sem_close(g_philo->meals);
		sem_close(g_philo->corpse);
		sem_close(g_philo->print);
		while (++i < g_philo->nb_philo)
		{
			free(g_philo->philo[i]);
		}
		free(g_philo->philo);
		free(g_philo);
	}
	g_philo = NULL;
	return (status);
}
