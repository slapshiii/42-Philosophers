/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 13:26:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_param(char **av, t_philo *data)
{
	if (((data)->nb_philo = ft_atoi(av[1])) < 2)
		return (ERR_NUM_PHILO);
	if (((data)->time_to_die = ft_atoi(av[2])) < 1)
		return (ERR_TIME);
	if (((data)->time_to_eat = ft_atoi(av[3])) < 1)
		return (ERR_TIME);
	if (((data)->time_to_sleep = ft_atoi(av[4])) < 1)
		return (ERR_TIME);
	if (av[5] != NULL && ((data)->nb_must_eat = ft_atoi(av[5])) < MIN_EAT)
		return (ERR_NUM_PHILO);
	else if (av[5] == NULL)
		(data)->nb_must_eat = -1;
	return (SUCCESS);
}

static int	init_mutex(t_philo *data)
{
	int	i;

	i = 0;
	if (!(data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)
		* data->nb_philo)))
		return (ERR_MALLOC);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->meals, NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->state, NULL);
	return (SUCCESS);
}

int			get_param(char **av, t_philo *data)
{
	int	i;

	i = -1;
	if (init_param(av, data))
		return (ERR_INIT);
	if (init_mutex(data))
		return (ERR_INIT_MUTEX);
	return (SUCCESS);
}
