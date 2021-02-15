/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 13:35:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(void *arg)
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
			if (ph[i].data->nb_must_eat ==
			(ph[0].data->nb_philo * ph[0].data->nb_must_eat))
			{
				pthread_mutex_lock(&ph[i].data->print);
				printf("All philosophers have eaten\n");
				pthread_mutex_lock(&ph[i].data->state);
				ph[i].data->status = ENDED;
				pthread_mutex_unlock(&ph[i].data->state);
				pthread_mutex_unlock(&ph[i].data->print);
			}
			i++;
		}
	}
	return (NULL);
}

void	*report_corpse(void *arg)
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
	}
	return (NULL);
}