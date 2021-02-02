/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 15:37:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_param(void)
{
	if (!(g_philo = (t_philo*)malloc(sizeof(t_philo))))
		return (FAILED);
	memset(g_philo, 0, sizeof(t_philo));
	sem_unlink(SEM_LOCK);
	if ((g_philo->lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL,
		0660, 2)) == SEM_FAILED)
		return (FAILED);
	sem_unlink(SEM_PRINT);
	if ((g_philo->print = sem_open(SEM_PRINT, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (FAILED);
	return (SUCCESS);
}

static int	init_philo(void)
{
	int i;

	i = -1;
	sem_unlink(SEM_FORK);
	if ((g_philo->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL,
		0660, g_philo->nb_philo)) == SEM_FAILED)
		return (FAILED);
	if (!(g_philo->threads = (pthread_t*)malloc(sizeof(pthread_t)
		* (g_philo->nb_philo + 1))))
		return (FAILED);
	if (!(g_philo->last_eaten = (struct timeval*)malloc(sizeof(struct timeval)
		* g_philo->nb_philo)))
		return (FAILED);
	if (!(g_philo->has_eaten = (int*)malloc(sizeof(int) * g_philo->nb_philo)))
		return (FAILED);
	memset(g_philo->threads, 0, sizeof(pthread_t) * (g_philo->nb_philo + 1));
	memset(g_philo->last_eaten, 0, sizeof(struct timeval) * g_philo->nb_philo);
	memset(g_philo->has_eaten, 0, sizeof(int) * g_philo->nb_philo);
	while (++i < g_philo->nb_philo)
	{
		gettimeofday(&(g_philo->last_eaten[i]), NULL);
	}
	return (SUCCESS);
}

int			get_param(char **av)
{
	if (init_param())
		return (ERR_MALLOC);
	if (((g_philo)->nb_philo = ft_atoi(av[1])) < 1)
		return (ERR_NUM_PHILO);
	if (((g_philo)->time_to_die = ft_atoi(av[2])) < 1)
		return (ERR_TIME);
	if (((g_philo)->time_to_eat = ft_atoi(av[3]) * 1000) < 1)
		return (ERR_TIME);
	if (((g_philo)->time_to_sleep = ft_atoi(av[4]) * 1000) < 1)
		return (ERR_TIME);
	if (av[5] != NULL && ((g_philo)->nb_must_eat = ft_atoi(av[5])) < MIN_EAT)
		return (ERR_NUM_PHILO);
	else if (av[5] == NULL)
		(g_philo)->nb_must_eat = -1;
	if (init_philo())
		return (ERR_INIT_MUTEX);
	return (SUCCESS);
}
