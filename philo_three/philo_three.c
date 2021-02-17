/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 10:25:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_end(t_data *philo, int i)
{
	sem_wait(philo[i].data->print);
	printf("All philosophers have eaten\n");
	sem_wait(philo[i].data->state);
	philo[i].data->status = ENDED;
	sem_post(philo[i].data->state);
	sem_post(philo[i].data->print);
}

void		*checker_dead(void *arg)
{
	t_data	*ph;
	int		i;

	ph = (t_data*)arg;
	i = 0;
	sem_wait(ph->data->corpse);
	if (ph->data->status != RUNNING)
		return (NULL);
	ph->data->status = DIED;
	while (i < ph->data->nb_philo)
	{
		ph[i].status = ENDED;
		sem_post(ph->data->meals);
		kill(ph[i].pid, SIGKILL);
		i++;
	}
	return (NULL);
}

void		*checker_meal(void *arg)
{
	t_data	*ph;
	int		i;

	ph = (t_data*)arg;
	i = 0;
	while (i < ph->data->nb_philo)
	{
		sem_wait(ph->data->meals);
		i++;
	}
	if (ph->data->status != RUNNING)
		return (NULL);
	print_end(ph, 0);
	ph->data->status = ENDED;
	i = 0;
	while (i < ph->data->nb_philo)
	{
		ph[i].status = ENDED;
		kill(ph[i].pid, SIGKILL);
		i++;
	}
	sem_post(ph->data->corpse);
	return (NULL);
}

void		*report(void *arg)
{
	t_data	*ph;

	ph = (t_data*)arg;
	while (42 && !ph->status)
	{
		if (get_timestamp() - ph->last_meal > ph->data->time_to_die)
		{
			print_msg(ph, MSG_DIED);
			sem_post(ph->data->corpse);
			ph->status = DIED;
			return (NULL);
		}
		if (ph->data->nb_must_eat != -1 && ph->eaten >= ph->data->nb_must_eat)
		{
			print_msg(ph, MSG_ENDED);
			sem_post(ph->data->meals);
			ph->status = ENDED;
			return (NULL);
		}
		usleep(10);
	}
	return (NULL);
}
