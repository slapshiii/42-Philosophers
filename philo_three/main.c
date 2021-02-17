/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/17 10:03:47 by user42           ###   ########.fr       */
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
		res[i].last_meal = get_timestamp();
		i++;
	}
	return (res);
}

static int		launch_philo(t_data *philo, int i)
{
	if ((philo[i].pid = fork()) == -1)
		return (ERR_INIT);
	if (philo[i].pid == 0)
	{
		philo_monitor((void*)&philo[i]);
		exit(0);
	}
	return (0);
}

void			launch_thread(t_philo *data, t_data *philo)
{
	pthread_t	monitor_meal;
	pthread_t	monitor_dead;
	int			i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (launch_philo(philo, i))
		{
			write(2, "process create error\n", 21);
			return ;
		}
		usleep(20);
		i++;
	}
	pthread_create(&monitor_meal, NULL, &checker_meal, (void*)philo);
	pthread_create(&monitor_dead, NULL, &checker_dead, (void*)philo);
	pthread_join(monitor_meal, NULL);
	pthread_join(monitor_dead, NULL);
}

/*
**	nb_philo; time_to_die; time_to_eat; time_to_sleep; nb_must_eat
*/

int				main(int ac, char **av)
{
	t_philo	data;
	t_data	*philo;

	philo = NULL;
	memset(&data, 0, sizeof(t_philo));
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
