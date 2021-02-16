/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:37:25 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 16:05:14 by user42           ###   ########.fr       */
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
	sem_unlink(SEM_DEAD);
	if ((data->forks = sem_open(SEM_FORK, O_CREAT | O_EXCL,
		0660, data->nb_philo)) == SEM_FAILED)
		return (ERR_INIT + 10);
	if ((data->meals = sem_open(SEM_MEAL, O_CREAT | O_EXCL,
		0660, 0)) == SEM_FAILED)
		return (ERR_INIT + 11);
	if ((data->state = sem_open(SEM_STAT, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (ERR_INIT + 12);
	if ((data->print = sem_open(SEM_MSGS, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (ERR_INIT + 13);
	if ((data->lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL,
		0660, 1)) == SEM_FAILED)
		return (ERR_INIT + 14);
	if ((data->corpse = sem_open(SEM_DEAD, O_CREAT | O_EXCL,
		0660, 0)) == SEM_FAILED)
		return (ERR_INIT + 15);
	return (SUCCESS);
}

int			get_param(char **av, t_philo *data)
{
	if (init_param(av, data))
		return (ERR_INIT);
	return (init_sem(data));
}
