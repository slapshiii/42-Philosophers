/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:32:30 by user42            #+#    #+#             */
/*   Updated: 2021/02/05 18:21:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	{
		fprintf(stderr, "An error has occured\n");
		return (clean_exit(status));
	}
	if ((status = launch_thread()) == -1)
		fprintf(stderr, "An error has occured thread\n");
	return (clean_exit(status));
}
