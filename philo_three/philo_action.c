/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:53:34 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 17:17:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *arg)
{
	t_data		*philo;
	pthread_t	monitor;

	philo = (t_data*)arg;
	philo->last_meal = get_timestamp();
	pthread_create(&monitor, NULL, &report, (void*)philo);
	pthread_detach(monitor);
	while (42 && !philo->status)
	{
		philo_fork(philo);
		philo_eat(philo);
		philo_rest(philo);
	}
	return (NULL);
}

void	philo_fork(t_data *philo)
{
	sem_wait(philo->data->lock);
	sem_wait(philo->data->forks);
	print_msg(philo, MSG_FORK);
	sem_wait(philo->data->forks);
	sem_post(philo->data->lock);
	print_msg(philo, MSG_FORK);
}

void	philo_eat(t_data *philo)
{
	print_msg(philo, MSG_EAT);
	philo->last_meal = get_timestamp();
	my_usleep(philo->data->time_to_eat);
	philo->eaten++;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	philo_rest(t_data *philo)
{
	print_msg(philo, MSG_SLEEP);
	my_usleep(philo->data->time_to_sleep);
	print_msg(philo, MSG_THINK);
}
