/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plee <plee@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:21:27 by plee              #+#    #+#             */
/*   Updated: 2021/11/08 15:27:23 by plee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_error(char *str)
{
	printf("%s", str);
	return (0);
}

static int	init_thread_fork(t_philo **philos, t_info *info)
{
	int	i;

	i = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philos);
	if (*philos == NULL)
		return (FAIL);
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->num_of_philos);
	if (info->fork == NULL)
	{
		free(*philos);
		return (FAIL);
	}
	while (i < info->num_of_philos)
		pthread_mutex_init(&info->fork[i++], NULL);
	pthread_mutex_init(&info->print_state, NULL);
	pthread_mutex_init(&info->anyone_dead, NULL);
	return (SUCCESS);
}

static int	parse_info(int argc, char **argv, t_info *info)
{
	memset(info, 0, sizeof(t_info));
	if ((!ft_isdigit(*(argv[1])) || !ft_isdigit(*(argv[2]))
			|| !ft_isdigit(*(argv[3])) || !ft_isdigit(*(argv[4])))
		|| (argc == 6 && !ft_isdigit(*(argv[5]))))
		return (FAIL);
	info->num_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		info->num_of_time_must_eat = -1;
	else
		info->num_of_time_must_eat = ft_atoi(argv[5]);
	if (info->num_of_philos < 0 || info->time_to_die < 0
		|| info->time_to_eat < 0 || info->time_to_sleep < 0
		|| (info->num_of_time_must_eat && argc == 6 < 0))
		return (FAIL);
	info->start_time = get_time();
	info->all_alive = SUCCESS;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (print_error("Wrong num of Arguments"));
	if (parse_info(argc, argv, &info) == FAIL)
		return (print_error("Parsing Error"));
	if (init_thread_fork(&philos, &info) == FAIL)
		return (print_error("Malloc Error"));
	start_dining(philos, &info);
	free_philos(philos);
	return (0);
}
