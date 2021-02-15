/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:34:51 by user42            #+#    #+#             */
/*   Updated: 2021/02/15 13:28:43 by user42           ###   ########.fr       */
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

# define RUNNING 0
# define ENDED 1
# define DIED 2

# define MSG_FORK " has taken a fork\n"
# define MSG_EAT " is eating\n"
# define MSG_SLEEP " is sleeping\n"
# define MSG_THINK " is thinking\n"
# define MSG_DIED " died\n"
# define MSG_ENDED " finished\n"

typedef struct	s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	int				status;
	int				finished;
	pthread_mutex_t	meals;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state;
}				t_philo;

typedef struct	s_data
{
	pthread_mutex_t	*f_fork;
	pthread_mutex_t	*s_fork;
	t_philo			*data;
	int				id;
	long			last_meal;
	pthread_t		monitor;
}				t_data;

int				get_param(char **av, t_philo *data);

int				clean_exit(t_philo *data, t_data *philo);

void			*report_corpse(void *arg);
void			launch_thread(t_philo *data, t_data *philo);

void			*checker(void *arg);
void			*philo_monitor(void *arg);
void			philo_fork(t_data *philo);
void			philo_eat(t_data *philo);
void			philo_rest(t_data *philo);

void			print_msg(t_data *philo, char *msg);

char			*ft_strcat(char *dest, const char *srcs);
char			*ft_strcpy(char *dest, const char *srcs);
size_t			ft_strlen(char *str);
long			get_timestamp(void);
int				is_whitespace(char c);
int				ft_atoi(const char *s);
char			*ft_itoa_dec(int num, char *res);
char			*reverse(char *str, int len);
void			my_sleep(int time);

#endif
