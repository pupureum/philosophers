/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plee <plee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:35:24 by plee              #+#    #+#             */
/*   Updated: 2021/11/08 15:28:55 by plee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	unsigned long	ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ms);
}

void	free_philos(t_philo *philos)
{
	int		i;
	t_info	*info;

	i = 0;
	info = philos->info;
	while (i < info->num_of_philos)
		pthread_mutex_destroy(&info->fork[i++]);
	free(info->fork);
	free(philos);
}

void	print_state(t_philo *philo, int state)
{
	unsigned long	now;
	t_info			*info;

	now = get_time() - philo->info->start_time;
	info = philo->info;
	if (info->all_alive == SUCCESS && state == FORK)
		printf("\e[33m%lums \e[96m%d %s", now, philo->id, S_FORK);
	else if (info->all_alive == SUCCESS && state == EAT)
		printf("\e[33m%lums \e[96m%d %s", now, philo->id, S_EAT);
	else if (info->all_alive == SUCCESS && state == SLEEP)
		printf("\e[33m%lums \e[96m%d %s", now, philo->id, S_SLEEP);
	else if (info->all_alive == SUCCESS && state == THINK)
		printf("\e[33m%lums \e[96m%d %s", now, philo->id, S_THINK);
	else if (state == DIE)
		printf("\e[33m%lums \e[96m%d %s", now, philo->id, S_DIE);
}

int	ft_isdigit(int c)
{
	if ((c >= '0') && (c <= '9'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	ans;
	int	minus;

	minus = 1;
	ans = 0;
	while ((*str >= 9 && *str <= 13) || (*str == ' '))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		ans = ans * 10 + (*str - '0') * minus;
		str++;
	}
	return (ans);
}
