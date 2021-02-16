/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:18:56 by user42            #+#    #+#             */
/*   Updated: 2021/02/16 11:02:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcpy(char *dest, const char *srcs)
{
	int	i;

	i = 0;
	while (srcs[i] != '\0')
	{
		dest[i] = srcs[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlen(char *str)
{
	size_t	res;

	res = 0;
	while (str && str[res])
		res++;
	return (res);
}

char	*reverse(char *str, int len)
{
	int		i;
	char	c;

	i = 0;
	while (i <= len / 2)
	{
		c = str[i];
		str[i] = str[len - i];
		str[len - i] = c;
		i++;
	}
	return (str);
}

void	my_usleep(int time, int id)
{
	long			target;
	long			now;

	now = 0;
	target = get_timestamp();
	target += time;
	usleep((time - 10) * 1000);
	while (target > now)
	{
		now = get_timestamp();
	}
}
