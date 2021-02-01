/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 18:27:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(void *arg)
{
	int res;

	while ((res = is_dead()) == 0)
		;
	thread_cancel(res);
	*(int*)arg = res;
	return (arg);
}

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
			return (2);
		if (get_timestamp(&time)
			- get_timestamp(&(g_philo->last_eaten[i])) > g_philo->time_to_die)
			return (1);
		i++;
	}
	return (0);
}

int	thread_cancel(int res)
{
	int i;

	i = 0;
	while (i < g_philo->nb_philo)
	{
		pthread_cancel(g_philo->threads[i]);
		i++;
	}
	if (res == 1)
		print_msg(i + 1, MSG_DIED);
	else
		printf("finished\n");
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

void	*routine(void *i)
{
	int id_philo;
	int nb_turn;

	id_philo = (*(int*)i);
	nb_turn = 0;
	g_philo->has_eaten[id_philo - 1] = 0;
	while (nb_turn < g_philo->nb_must_eat || g_philo->nb_must_eat == -1)
	{
		sem_wait(g_philo->forks);
		print_msg(id_philo, MSG_FORK);
		sem_wait(g_philo->forks);
		print_msg(id_philo, MSG_FORK);
		print_msg(id_philo, MSG_EAT);
		gettimeofday(&(g_philo->last_eaten[id_philo - 1]), NULL);
		g_philo->has_eaten[id_philo - 1]++;
		usleep(g_philo->time_to_eat);
		print_msg(id_philo, MSG_SLEEP);
		sem_post(g_philo->forks);
		sem_post(g_philo->forks);
		usleep(g_philo->time_to_sleep);
		print_msg(id_philo, MSG_THINK);
	}
	return (SUCCESS);
}