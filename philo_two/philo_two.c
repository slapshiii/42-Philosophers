/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 17:36:25 by user42           ###   ########.fr       */
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

void		*checker(void *arg)
{
	t_data	*ph;
	int		i;

	ph = (t_data*)arg;
	while (42 && ph[0].data->status != ENDED && ph[0].data->status != DIED)
	{
		i = 0;
		while (i < ph[0].data->nb_philo && ph[0].data->status != ENDED &&
		ph[0].data->status != DIED)
		{
			if (ph[0].data->nb_must_eat != -1 && ph[i].data->finished >=
				(ph[0].data->nb_philo * ph[0].data->nb_must_eat))
			{
				print_end(ph, i);
			}
			i++;
		}
		usleep(1);
	}
	return (NULL);
}

void		*report_corpse(void *arg)
{
	t_data	*ph;

	ph = (t_data*)arg;
	while (42 && ph->data->status != DIED && ph->data->status != ENDED)
	{
		if (get_timestamp() - ph->last_meal > ph->data->time_to_die)
		{
			print_msg(ph, MSG_DIED);
			sem_wait(ph->data->state);
			ph->data->status = DIED;
			sem_post(ph->data->state);
			break ;
		}
		usleep(10);
	}
	return (NULL);
}
