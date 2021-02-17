/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 10:03:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*init_thread(t_philo *data)
{
	t_data	*res;
	int		i;

	i = 0;
	if (!(res = (t_data*)malloc(sizeof(t_data) * data->nb_philo)))
		return (NULL);
	memset(res, 0, sizeof(t_data) * data->nb_philo);
	while (i < data->nb_philo)
	{
		res[i].id = i;
		res[i].data = data;
		res[i].f_fork = &data->forks[i];
		if (i == 0)
			res[i].s_fork = &data->forks[data->nb_philo - 1];
		else
			res[i].s_fork = &data->forks[i - 1];
		res[i].last_meal = get_timestamp();
		i++;
	}
	return (res);
}

void			launch_thread(t_philo *data, t_data *philo)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].monitor, NULL,
			philo_monitor, &philo[i]) < 0)
		{
			write(2, "thread create error\n", 20);
			return ;
		}
		usleep(20);
		i++;
	}
	pthread_create(&monitor, NULL, &checker, (void *)philo);
	pthread_detach(monitor);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(philo[i++].monitor, NULL);
}

/*
**	nb_philo; time_to_die; time_to_eat; time_to_sleep; nb_must_eat
*/

int				main(int ac, char **av)
{
	t_philo	data;
	t_data	*philo;

	philo = NULL;
	if (ac < 5 || ac > 6)
		return (ERR_NUM_ARG);
	else
	{
		if ((data.status = get_param(av, &data)))
		{
			write(2, "An error has occured\n", 21);
			return (clean_exit(&data, philo));
		}
		philo = init_thread(&data);
		launch_thread(&data, philo);
		clean_exit(&data, philo);
	}
	return (0);
}
