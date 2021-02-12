/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 14:19:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	report_corpse(void)
{
	struct timeval	time;
	int				diff;
	int				time_i;
	int				time_p;
	int				i;

	i = 0;
	while (i < g_philo->nb_philo)
	{
		gettimeofday(&time, NULL);
		time_i = get_timestamp(&time);
		time_p = get_timestamp(&g_philo->philo[i]->last_meal);
		diff = time_i - time_p;
		if (!g_philo->philo[i]->is_eating && diff > g_philo->time_to_die)
		{
			print_msg(g_philo->philo[i]->id, MSG_DIED);
			g_philo->status = 0;
			g_philo->philo[i]->status = 0;
		}
		i++;
	}
}
