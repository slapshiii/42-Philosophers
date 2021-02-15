/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:38:53 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 13:29:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	get_size_num(int num)
{
	size_t		len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static void	ft_putstr(char *str)
{
	size_t	len;

	len  = ft_strlen(str);
	write(1, str, len);
}

static void	ft_putnbr(unsigned long n)
{
	char	line[11];
	size_t	i;

	i = get_size_num(n);
	line[i] = '\0';
	i--;
	if (n == 0)
		write(1, "0", 1);
	while (n > 0)
	{
		line[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	ft_putstr(line);
}

void		print_msg(t_data *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->print);
	if (philo->data->status != DIED && philo->data->status != ENDED)
	{
		timestamp = get_timestamp();
		ft_putnbr(timestamp);
		ft_putstr(" ");
		ft_putnbr(philo->id + 1);
		ft_putstr(msg);
	}
	pthread_mutex_unlock(&philo->data->print);
}
