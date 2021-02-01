/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:30:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/01 15:31:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		is_whitespace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

int		ft_atoi(const char *s)
{
	int res;
	int sig;

	res = 0;
	sig = -1;
	while (*s && is_whitespace(*s))
		++s;
	if (*s && *s == '-')
	{
		sig = 1;
		++s;
	}
	else if (*s && *s == '+')
		++s;
	while (*s && *s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		++s;
	}
	return (res * (-sig));
}

char	*ft_itoa_dec(int num)
{
	char	buf[11];
	char	*res;
	int		sig;

	sig = 0;
	res = &buf[sizeof(buf) - 1];
	*res = '\0';
	if (num < 0)
	{
		++sig;
		num *= -1;
	}
	*--res = '0' + (num % 10);
	num /= 10;
	while (num != 0)
	{
		*--res = '0' + (num % 10);
		num /= 10;
	}
	if (sig)
		*--res = '-';
	return (res);
}

int		get_timestamp(struct timeval *time)
{
	int res;

	res = time->tv_usec / 1000 + (time->tv_sec % 1000000) * 1000;
	return (res);
}
