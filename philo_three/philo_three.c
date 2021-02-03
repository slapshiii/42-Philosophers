/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:27:58 by user42            #+#    #+#             */
/*   Updated: 2021/02/03 14:45:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	routine(int id_philo)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	gettimeofday(&data.last_meal, NULL);
	pthread_create(&data.monitor,NULL, &checker, &data);
	while (!g_philo->status)
	{
		philo_fork(id_philo);
		philo_eat(id_philo);
		philo_rest(id_philo);	
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

static int	make_philo(int id, int *pid)
{
	if ((pid[id] = fork()) == -1)
		exit(clean_exit(1));
	if (pid[id] == 0)
	{
		exit(routine(id));
	}
	return (0);
}

int			launch_thread(void)
{
	pid_t	pid[g_philo->nb_philo];
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (i < g_philo->nb_philo)
	{
		make_philo(i, pid);
		i++;
	}
	waitpid(0, &res, 0);
	return (SUCCESS);
}