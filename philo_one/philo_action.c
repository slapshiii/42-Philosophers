/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:53:34 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 16:37:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *arg)
{
	t_data		*philo;
	pthread_t	monitor;

	philo = (t_data*)arg;
	pthread_create(&monitor, NULL, &report_corpse, (void *)philo);
	pthread_detach(monitor);
	philo->last_meal = get_timestamp();
	philo->id % 2 ? 0 : usleep(philo->data->time_to_eat * 1000);
	while (42 && philo->data->status != DIED && philo->data->status != ENDED)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_rest(philo);
	}
	return (NULL);
}

void	philo_fork(t_data *philo)
{
	pthread_mutex_lock(philo->f_fork);
	print_msg(philo, MSG_FORK);
	pthread_mutex_lock(philo->s_fork);
	print_msg(philo, MSG_FORK);
}

void	philo_eat(t_data *philo)
{
	print_msg(philo, MSG_EAT);
	philo->last_meal = get_timestamp();
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meals);
	philo->data->finished++;
	pthread_mutex_unlock(&philo->data->meals);
	pthread_mutex_unlock(philo->s_fork);
	pthread_mutex_unlock(philo->f_fork);
}

void	philo_rest(t_data *philo)
{
	print_msg(philo, MSG_SLEEP);
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo, MSG_THINK);
}
