/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 16:31:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_exit(int status)
{
	int i;

	i = 0;
	if (g_philo)
	{
		sem_unlink(SEM_LOCK);
		sem_unlink(SEM_FORK);
		sem_unlink(SEM_PRINT);
		sem_close(g_philo->lock);
		sem_close(g_philo->forks);
		sem_close(g_philo->print);
		free(g_philo->last_meal);
		g_philo->last_meal = NULL;
		free(g_philo->nb_meal);
		g_philo->nb_meal = NULL;
		free(g_philo);
	}
	g_philo = NULL;
	return (status);
}