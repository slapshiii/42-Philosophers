/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 20:34:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_param(char **av)
{
	if (!(g_philo = (t_philo*)malloc(sizeof(t_philo))))
		return (FAILED);
	memset(g_philo, 0, sizeof(t_philo));
	if (((g_philo)->nb_philo = ft_atoi(av[1])) < 2)
		return (ERR_NUM_PHILO);
	if (((g_philo)->time_to_die = ft_atoi(av[2])) < 1)
		return (ERR_TIME);
	if (((g_philo)->time_to_eat = ft_atoi(av[3])) < 1)
		return (ERR_TIME);
	if (((g_philo)->time_to_sleep = ft_atoi(av[4])) < 1)
		return (ERR_TIME);
	if (av[5] != NULL && ((g_philo)->nb_must_eat = ft_atoi(av[5])) < MIN_EAT)
		return (ERR_NUM_PHILO);
	else if (av[5] == NULL)
		(g_philo)->nb_must_eat = -1;
	return (SUCCESS);
}

static int	init_philo(void)
{
	int	i;

	i = -1;
	if (!(g_philo->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
		* g_philo->nb_philo)))
		return (ERR_MALLOC);
	if (!(g_philo->meals = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (ERR_MALLOC);
	if (!(g_philo->print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))))
		return (ERR_MALLOC);
	while (++i < g_philo->nb_philo)
		pthread_mutex_init(g_philo->forks + i, NULL);
	pthread_mutex_init(g_philo->meals, NULL);
	pthread_mutex_init(g_philo->print, NULL);
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
