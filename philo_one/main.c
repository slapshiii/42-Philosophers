/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 15:46:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*checker(void *arg)
{
	int res;

	while ((res = is_dead()) == 0)
		;
	thread_cancel();
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
	while (nb_turn < g_philo->nb_must_eat || g_philo->nb_must_eat == -1)
	{
		pthread_mutex_lock(&(g_philo->forks[id_philo - 1]));
		print_msg(id_philo, MSG_FORK);
		pthread_mutex_lock(&(g_philo->forks[id_philo % g_philo->nb_philo]));
		print_msg(id_philo, MSG_FORK);
		print_msg(id_philo, MSG_EAT);
		gettimeofday(&(g_philo->last_eaten[id_philo - 1]), NULL);
		g_philo->has_eaten[id_philo - 1]++;
		usleep(g_philo->time_to_eat);
		print_msg(id_philo, MSG_SLEEP);
		pthread_mutex_unlock(&(g_philo->forks[id_philo % g_philo->nb_philo]));
		pthread_mutex_unlock(&(g_philo->forks[id_philo - 1]));
		usleep(g_philo->time_to_sleep);
		print_msg(id_philo, MSG_THINK);
	}
	return (SUCCESS);
}

/*
**	nb_philo; time_to_die; time_to_eat; time_to_sleep; nb_must_eat
*/

int		main(int ac, char **av)
{
	int				status;
	int				i;

	status = 0;
	i = 0;
	if (ac < 5 || ac > 6)
		return (ERR_NUM_ARG);
	if ((status = get_param(av)))
		fprintf(stderr, "An error has occured\n");
	if ((status = launch_thread()) == -1)
		fprintf(stderr, "An error has occured thread\n");
	return (clean_exit(status));
}
