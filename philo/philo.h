/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plee <plee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 00:08:25 by plee              #+#    #+#             */
/*   Updated: 2021/11/08 15:27:18 by plee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

# define S_FORK		"\e[32mhas taken a fork\e[39m\n"
# define S_EAT		"\e[33mis eating\e[39m\n"
# define S_SLEEP	"\e[96mis sleeping\e[39m\n"
# define S_THINK	"\e[0;35mis thinking\e[39m\n"
# define S_DIE		"\033[0;31mdied\e[39m\n"

# define FAIL	0
# define SUCCESS	1
# define FORK	2
# define EAT	3
# define SLEEP	4
# define THINK	5
# define DIE	6

typedef struct s_info
{
	int				num_of_philos;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_of_time_must_eat;
	long			start_time;
	long			delay_time;
	int				all_alive;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_state;
	pthread_mutex_t	anyone_dead;
}				t_info;

typedef struct s_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				num_of_eat;
	unsigned long	last_eat;
	int				all_ate;
	pthread_t		thread;
	t_info			*info;
}					t_philo;

/*
utils.c
*/
unsigned long	get_time(void);
void			free_philos(t_philo *philos);
void			print_state(t_philo *philo, int state);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

/*
dine.c
*/
void			start_dining(t_philo *philos, t_info *info);

#endif