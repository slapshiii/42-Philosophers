/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:30:22 by user42            #+#    #+#             */
/*   Updated: 2021/02/14 14:40:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcat(char *dest, const char *srcs)
{
	size_t	i;
	char	*s;

	i = ft_strlen(dest);
	s = (char *)srcs;
	while (s && *s)
		dest[i++] = *(s++);
	dest[i] = '\0';
	return (dest);
}

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

char	*ft_itoa_dec(int num, char *res)
{
	int		i;
	int		sig;

	sig = 0;
	i = 0;
	memset(res, 0, sizeof(char) * 12);
	if (num < 0)
	{
		++sig;
		num *= -1;
	}
	res[i++] = '0' + (num % 10);
	num /= 10;
	while (num != 0)
	{
		res[i++] = '0' + (num % 10);
		num /= 10;
	}
	if (sig)
		res[i] = '-';
	reverse(res, i - 1);
	return (res);
}

long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}
