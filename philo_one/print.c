/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 11:06:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			print_msg(t_data *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->status != DIED && philo->data->status != ENDED)
	{
		timestamp = get_timestamp();
		printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
	}
	pthread_mutex_unlock(&philo->data->print);
}
