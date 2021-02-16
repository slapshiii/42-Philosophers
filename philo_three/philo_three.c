/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 15:10:49 by user42           ###   ########.fr       */
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
	while(i < ph->data->nb_philo)
	{
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
	ph->data->status = ENDED;
	sem_post(ph->data->corpse);
	i = 0;
	while (i < ph->data->nb_philo)
	{
		kill(ph[i].pid, SIGKILL);
		i++;
	}
	print_end(ph, 0);
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
			break ;
		}
		if (ph->eaten >= ph->data->nb_must_eat)
		{
			print_msg(ph, MSG_ENDED);
			sem_post(ph->data->meals);
			ph->status = ENDED;
			break ;
		}
		usleep(10);
	}
	return (NULL);
}
