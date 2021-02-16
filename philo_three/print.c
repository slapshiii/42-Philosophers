/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 12:02:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void			print_msg(t_data *philo, char *msg)
{
	long	timestamp;

	sem_wait(philo->data->print);
	if (philo->data->status != DIED && philo->data->status != ENDED)
	{
		timestamp = get_timestamp();
		printf("%ld %d %s\n", timestamp, philo->id + 1, msg);
	}
	sem_post(philo->data->print);
}
