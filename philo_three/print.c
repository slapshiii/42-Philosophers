/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 17:41:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(int id, int msg)
{
	struct timeval	time;
	char			str[50];

	gettimeofday(&time, NULL);
	if (msg == MSG_FORK)
		strcpy(str, "has taken a fork");
	else if (msg == MSG_EAT)
		strcpy(str, "is eating");
	else if (msg == MSG_SLEEP)
		strcpy(str, "is sleeping");
	else if (msg == MSG_THINK)
		strcpy(str, "is thinking");
	else if (msg == MSG_DIED)
		strcpy(str, "died");
	else if (msg == MSG_ENDED)
		strcpy(str, "finished");
	if (g_philo->status)
		printf("%d %d %s\n", get_timestamp(&time), id + 1, str);
}
