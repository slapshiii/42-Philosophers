/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 15:28:24 by user42           ###   ########.fr       */
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

void		print_msg(int id, char *msg)
{
	struct timeval	time;
	char			str[50];
	int				timestamp;
	char			char_time[12];
	char			char_id[12];

	if (!g_philo->status)
		return ;
	gettimeofday(&time, NULL);
	memset(str, 0, sizeof(str));
	timestamp = get_timestamp(&time);
	ft_itoa_dec(timestamp, char_time);
	ft_itoa_dec(id + 1, char_id);
	compose_msg(str, char_time, char_id, msg);
	pthread_mutex_lock(g_philo->print);
	write(1, str, ft_strlen(str));
	pthread_mutex_unlock(g_philo->print);
}
