/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/08 12:31:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_param(char **av)
{
	if (!(g_philo = (t_philo*)malloc(sizeof(t_philo))))
		return (FAILED);
	memset(g_philo, 0, sizeof(t_philo));
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
	return (SUCCESS);
}

static int	init_philo(void)
{
	sem_unlink(SEM_FORK);
	if ((g_philo->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL,
		0660, g_philo->nb_philo)) == SEM_FAILED)
		return (FAILED);
	sem_unlink(SEM_LOCK);
	if ((g_philo->lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL,
		0660, (g_philo->nb_philo) >> 1)) == SEM_FAILED)
		return (FAILED);
	sem_unlink(SEM_DEAD);
	if ((g_philo->corpse = sem_open(SEM_DEAD, O_CREAT | O_EXCL,
		0660, 0)) == SEM_FAILED)
		return (FAILED);
	sem_unlink(SEM_MEAL);
	if ((g_philo->meals = sem_open(SEM_MEAL, O_CREAT | O_EXCL,
		0660, 0)) == SEM_FAILED)
		return (FAILED);
	sem_unlink(SEM_MSGS);
	if ((g_philo->print = sem_open(SEM_MSGS, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (FAILED);
	return (SUCCESS);
}

int			get_param(char **av)
{
	int	i;

	i = -1;
	if (init_param(av))
		return (ERR_MALLOC);
	if (!(g_philo->philo = (t_data**)malloc(sizeof(t_data*)
		* g_philo->nb_philo)))
		return (ERR_MALLOC);
	while (++i < g_philo->nb_philo)
	{
		if (!(g_philo->philo[i] = data_philo(i)))
			return (ERR_MALLOC);
	}
	if (init_philo())
		return (ERR_INIT_MUTEX);
	return (SUCCESS);
}
