/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 14:31:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_end(t_data *philo, int i)
{
	pthread_mutex_lock(&philo[i].data->print);
	printf("All philosophers have eaten\n");
	pthread_mutex_lock(&philo[i].data->state);
	philo[i].data->status = ENDED;
	pthread_mutex_unlock(&philo[i].data->state);
	pthread_mutex_unlock(&philo[i].data->print);
}

void		*checker(void *arg)
{
	t_data	*ph;
	int		i;
	int		total;

	ph = (t_data*)arg;
	while (42 && ph[0].data->status != ENDED && ph[0].data->status != DIED)
	{
		i = 0;
		total = 0;
		while (i < ph[0].data->nb_philo && ph[0].data->status != ENDED &&
		ph[0].data->status != DIED)
		{
			if (ph[i].eaten >= ph[0].data->nb_must_eat)
			{
				total++;
				if (total == ph[0].data->nb_philo)
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
			pthread_mutex_lock(&ph->data->state);
			ph->data->status = DIED;
			pthread_mutex_unlock(&ph->data->state);
			break ;
		}
		usleep(1);
	}
	return (NULL);
}
