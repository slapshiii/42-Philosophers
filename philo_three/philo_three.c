/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/02 17:11:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine(int id_philo)
{
	gettimeofday(&(g_philo->last_meal[id_philo]), NULL);
	while (!g_philo->status)
	{
		sem_wait(g_philo->lock);
		sem_wait(g_philo->forks);
		print_msg(id_philo + 1, MSG_FORK);
		sem_wait(g_philo->forks);
		sem_post(g_philo->lock);
		print_msg(id_philo + 1, MSG_FORK);
		print_msg(id_philo + 1, MSG_EAT);
		usleep(g_philo->time_to_eat);
		gettimeofday(&(g_philo->last_meal[id_philo]), NULL);
		g_philo->nb_meal[id_philo]++;
		sem_post(g_philo->forks);
		sem_post(g_philo->forks);
		print_msg(id_philo + 1, MSG_SLEEP);
		usleep(g_philo->time_to_sleep);
		print_msg(id_philo + 1, MSG_THINK);
	}
	return (SUCCESS);
}

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
			&& g_philo->nb_meal[i] >= g_philo->nb_must_eat)
			return (-1);
		else if (int_time
		- get_timestamp(&(g_philo->last_meal[i])) > g_philo->time_to_die)
			return (i + 1);
		i++;
	}
	return (0);
}

static void	*checker(void *arg)
{
	int res;

	while ((res = is_dead()) == 0)
		;
	sem_wait(g_philo->print);
	g_philo->status = 1;
	sem_post(g_philo->print);
	if (res == -1)
		printf("finished\n");
	else
		print_msg(res, MSG_DIED);
	*(int*)arg = res;
	return (arg);
}

/*
static void	kill_process(int *tab_pid)
{
	int	i;

	i = 0;
	while (i < g_philo->nb_philo)
	{
		kill(tab_pid[i], 130);
		i++;
	}
}*/

static int	make_philo(int id, int *pid)
{
	if ((pid[id] = fork()) == -1)
			exit(clean_exit(1));
	if (pid[id] == 0)
		exit(routine(id));
	return (0);
}

int			launch_thread(void)
{
	pid_t	pid[g_philo->nb_philo];
	int		i;
	void	*ptr;
	int		res;

	i = 0;
	res = 0;
	ptr = &res;
	while (i < g_philo->nb_philo)
	{
		make_philo(i, pid);
		i++;
	}
	if (pthread_create(g_philo->monitor, NULL, &checker, (void*)&res))
		return (FAILED);
	pthread_join(*g_philo->monitor, &ptr);
	while (--i >= 0)
		kill(pid[i], SIGKILL);
	return (SUCCESS);
}