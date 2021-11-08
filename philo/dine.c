/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dine.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plee <plee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 00:08:04 by plee              #+#    #+#             */
/*   Updated: 2021/11/08 15:27:26 by plee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*check_death(void *ptr)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)ptr;
	info = philo->info;
	while (SUCCESS)
	{
		if (info->all_alive == FAIL
			|| philo->num_of_eat == philo->info->num_of_time_must_eat)
			break ;
		pthread_mutex_lock(&info->anyone_dead);
		if (get_time() - philo->last_eat > info->time_to_die)
		{
			info->all_alive = FAIL;
			pthread_mutex_unlock(&info->fork[philo->right_fork]);
			print_state(philo, DIE);
			return (NULL);
		}
		pthread_mutex_unlock(&info->anyone_dead);
		usleep(20);
	}
	return (NULL);
}

static void	spend_time(unsigned long time)
{
	unsigned long	end;

	end = get_time() + time;
	while (get_time() < end)
		usleep(100);
}

static void	pickup_forks(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if ((philo->id % 2 == 0 && !pthread_mutex_lock(&info->fork
				[philo->left_fork])) || !pthread_mutex_lock(&info->fork
			[philo->right_fork]))
		print_state(philo, FORK);
	if ((philo->id % 2 == 0 && !pthread_mutex_lock(&info->fork
				[philo->right_fork])) || !pthread_mutex_lock
		(&info->fork[philo->left_fork]))
		print_state(philo, FORK);
	philo->last_eat = get_time();
	print_state(philo, EAT);
	spend_time(info->time_to_eat);
	pthread_mutex_unlock(&info->fork[philo->right_fork]);
	pthread_mutex_unlock(&info->fork[philo->left_fork]);
	philo->num_of_eat++;
}

static void	*dine(void *ptr)
{
	t_info		*info;
	t_philo		*philo;
	pthread_t	monitor;

	philo = (t_philo *)ptr;
	info = philo->info;
	pthread_create(&monitor, NULL, check_death, philo);
	while (SUCCESS)
	{
		if (info->all_alive == FAIL)
			break ;
		pickup_forks(philo);
		if (info->num_of_time_must_eat != -1
			&& info->num_of_time_must_eat == philo->num_of_eat)
			break ;
		print_state(philo, SLEEP);
		spend_time(info->time_to_sleep);
		print_state(philo, THINK);
	}
	pthread_join(monitor, NULL);
	return (NULL);
}

void	start_dining(t_philo *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = i;
		if (i == 0)
			philos[i].left_fork = info->num_of_philos - 1;
		else
			philos[i].left_fork = i - 1;
		philos[i].num_of_eat = 0;
		philos[i].last_eat = get_time();
		philos[i].info = info;
		pthread_create(&philos[i].thread, NULL, dine, &philos[i]);
		i++;
	}	
	i = 0;
	while (i < info->num_of_philos)
		pthread_join(philos[i++].thread, NULL);
}
