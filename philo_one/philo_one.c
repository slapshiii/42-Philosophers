/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 14:19:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_dead(void)
{
	int				i;
	struct timeval	time;
	int				int_time;

	i = 0;
	gettimeofday(&(time), NULL);
	int_time = get_timestamp(&time);
	while (i < g_philo->nb_philo)
	{
		if (g_philo->nb_must_eat != -1
			&& g_philo->has_eaten[i] >= g_philo->nb_must_eat)
			return (-1);
		else if (int_time
		- get_timestamp(&(g_philo->last_eaten[i])) > g_philo->time_to_die)
			return (i + 1);
		i++;
	}
	return (0);
}

int		thread_cancel(void)
{
	int i;

	i = 0;
	while (i < g_philo->nb_philo)
	{
		pthread_join(g_philo->threads[i], NULL);
		i++;
	}
	return (0);
}

void	*checker(void *arg)
{
	int res;

	while ((res = is_dead()) == 0)
		;
	g_philo->status = 1;
	if (res == -1)
		printf("finished\n");
	else
		print_msg(res, MSG_DIED);
	*(int*)arg = res;
	return (arg);
}

void	*routine(void *i)
{
	int id_philo;
	int nb_turn;

	id_philo = (*(int*)i);
	nb_turn = 0;
	g_philo->has_eaten[id_philo - 1] = 0;
	while (g_philo->status == 0)
	{
		pthread_mutex_lock(&(g_philo->forks[g_philo->nb_philo]));
		pthread_mutex_lock(&(g_philo->forks[id_philo - 1]));
		print_msg(id_philo, MSG_FORK);
		pthread_mutex_lock(&(g_philo->forks[id_philo % g_philo->nb_philo]));
		pthread_mutex_unlock(&(g_philo->forks[g_philo->nb_philo]));
		print_msg(id_philo, MSG_FORK);
		print_msg(id_philo, MSG_EAT);
		usleep(g_philo->time_to_eat);
		gettimeofday(&(g_philo->last_eaten[id_philo - 1]), NULL);
		g_philo->has_eaten[id_philo - 1]++;
		pthread_mutex_unlock(&(g_philo->forks[id_philo % g_philo->nb_philo]));
		pthread_mutex_unlock(&(g_philo->forks[id_philo - 1]));
		print_msg(id_philo, MSG_SLEEP);
		usleep(g_philo->time_to_sleep);
		print_msg(id_philo, MSG_THINK);
	}
	return (SUCCESS);
}

int		launch_thread(void)
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
		++i;
	}
	pthread_join(g_philo->threads[g_philo->nb_philo], &ptr);
	thread_cancel();
	return (SUCCESS);
}
