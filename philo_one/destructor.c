/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:29 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 13:26:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	clean_mutex(t_philo *data)
{
	int i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->forks)[i]);
		i++;
	}
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->state));
	pthread_mutex_destroy(&(data->meals));
}

int			clean_exit(t_philo *data, t_data *philo)
{
	int	res;

	res = data->status;
	clean_mutex(data);
	free(data->forks);
	data->forks = NULL;
	free(philo);
	philo = NULL;
	return (res);
}
