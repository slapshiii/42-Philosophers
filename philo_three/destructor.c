/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 15:15:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_sem(t_philo *data)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_MSGS);
	sem_unlink(SEM_MEAL);
	sem_unlink(SEM_STAT);
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_DEAD);
	sem_close(data->forks);
	sem_close(data->meals);
	sem_close(data->print);
	sem_close(data->state);
	sem_close(data->lock);
	sem_close(data->corpse);
}

int			clean_exit(t_philo *data, t_data *philo)
{
	int	res;

	res = data->status;
	clean_sem(data);
	free(philo);
	philo = NULL;
	return (res);
}
