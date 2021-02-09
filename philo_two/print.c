/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/09 13:00:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	compose_msg(char *res, char *time, char *id, char *code)
{
	int	i;

	i = 0;
	while (*time)
		res[i++] = *(time++);
	res[i++] = ' ';
	while (*id)
		res[i++] = *(id++);
	res[i++] = ' ';
	while (*code)
		res[i++] = *(code++);
	res[i++] = '\n';
}

void		print_msg(int id, int msg)
{
	struct timeval	time;
	char			str[50];
	int				timestamp;
	char			char_time[12];
	char			char_id[12];

	gettimeofday(&time, NULL);
	memset(str, 0, sizeof(str));
	timestamp = get_timestamp(&time);
	ft_itoa_dec(timestamp, char_time);
	ft_itoa_dec(id + 1, char_id);
	if (msg == MSG_FORK)
		compose_msg(str, char_time, char_id, "has taken a fork");
	else if (msg == MSG_EAT)
		compose_msg(str, char_time, char_id, "is eating");
	else if (msg == MSG_SLEEP)
		compose_msg(str, char_time, char_id, "is sleeping");
	else if (msg == MSG_THINK)
		compose_msg(str, char_time, char_id, "is thinking");
	else if (msg == MSG_DIED)
		compose_msg(str, char_time, char_id, "died");
	else if (msg == MSG_ENDED)
		compose_msg(str, char_time, char_id, "finished");
	if (g_philo->status)
		write(1, str, ft_strlen(str));
}
