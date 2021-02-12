/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:34:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/12 14:12:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>

# define MIN_EAT 1

# define SUCCESS 0
# define FAILED -1

# define ERR_MALLOC 1
# define ERR_NUM_ARG 2
# define ERR_NUM_PHILO 3
# define ERR_TIME 4
# define ERR_INIT 5
# define ERR_INIT_MUTEX 6

# define MSG_FORK 0
# define MSG_EAT 1
# define MSG_SLEEP 2
# define MSG_THINK 3
# define MSG_DIED 4
# define MSG_ENDED 5

typedef struct	s_data
{
	int				status;
	int				nb_meal;
	int				id;
	int				is_eating;
	struct timeval	last_meal;
	pthread_t		monitor;
	pthread_t		main;
}				t_data;

typedef struct	s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				status;
	int				finished;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
	t_data			**philo;
}				t_philo;

t_philo			*g_philo;

int				get_param(char **av);

int				clean_exit(int status);

void			report_corpse(void);
void			report_meal(void);
void			*watcher_loop(void *arg);
void			launch_thread(void);

t_data			*data_philo(int i);
void			*philo_monitor(void *arg);
void			philo_fork(t_data *philo);
void			philo_eat(t_data *philo);
void			philo_rest(t_data *philo);

void			print_msg(int id, int msg);

char			*ft_strcat(char *dest, const char *srcs);
char			*ft_strcpy(char *dest, const char *srcs);
size_t			ft_strlen(char *str);
int				get_timestamp(struct timeval *time);
int				is_whitespace(char c);
int				ft_atoi(const char *s);
char			*ft_itoa_dec(int num, char *res);
char			*reverse(char *str, int len);

#endif
