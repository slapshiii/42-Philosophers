/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 15:52:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(void)
{
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&(time), NULL);
	while (i < g_philo->nb_philo)
	{
		if (g_philo->nb_must_eat != -1
			&& g_philo->has_eaten[i] >= g_philo->nb_must_eat)
		{
			printf("finished\n");
			return (2);
		}
		if (get_timestamp(&time)
			- get_timestamp(&(g_philo->last_eaten[i])) > g_philo->time_to_die)
		{
			print_msg(i, MSG_DIED);
			return (1);
		}
		i++;
	}
	return (0);
}

int	thread_cancel(void)
{
	int i;

	i = 0;
	while (i < g_philo->nb_philo)
	{
		pthread_cancel(g_philo->threads[i]);
		i++;
	}
	return (0);
}

int	launch_thread(void)
{
	int		index[g_philo->nb_philo + 1];
	int		i;
	void	*ptr;
	int		res;

	if (gettimeofday((g_philo)->time_start, NULL))
		return (FAILED);
	i = 0;
	ptr = &(index[g_philo->nb_philo]);
	if (pthread_create(&(g_philo->threads[g_philo->nb_philo]),
		NULL, &checker, ptr))
		return (FAILED);
	while (i < g_philo->nb_philo)
	{
		index[i] = i + 1;
		if ((res = pthread_create(&(g_philo->threads[i]),
			NULL, &routine, (void*)&index[i])))
			return (FAILED);
		if ((res = pthread_detach(g_philo->threads[i])))
			return (FAILED);
		++i;
	}
	pthread_join(g_philo->threads[g_philo->nb_philo], &ptr);
	return (SUCCESS);
}
