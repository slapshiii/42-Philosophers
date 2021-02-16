/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 10:50:34 by user42           ###   ########.fr       */
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

static int	init_sem(t_philo *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MSGS);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_STAT);
	sem_unlink(SEM_LOCK);
	if ((data->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL,
		0660, data->nb_philo)) == SEM_FAILED)
		return (ERR_INIT);
	if ((data->meals = sem_open(SEM_MEAL, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (ERR_INIT);
	if ((data->state = sem_open(SEM_STAT, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (ERR_INIT);
	if ((data->print = sem_open(SEM_MSGS, O_CREAT | O_EXCL,
		0660, 2)) == SEM_FAILED)
		return (ERR_INIT);
	if ((data->lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL,
		0660, data->nb_philo / 2)) == SEM_FAILED)
		return (ERR_INIT);
	return (SUCCESS);
}

int			get_param(char **av, t_philo *data)
{
	int	i;

	i = -1;
	if (init_param(av, data))
		return (ERR_INIT);
	if (init_sem(data))
		return (ERR_INIT_MUTEX);
	return (SUCCESS);
}
