/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 18:11:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clean_exit(int status)
{
	int i;

	i = 0;
	if (g_philo)
	{
		sem_unlink("forks");
		sem_close(g_philo->forks);
		free(g_philo->threads);
		g_philo->threads = NULL;
		free(g_philo->last_eaten);
		g_philo->last_eaten = NULL;
		free(g_philo->has_eaten);
		g_philo->has_eaten = NULL;
		free(g_philo);
	}
	g_philo = NULL;
	return (status);
}
