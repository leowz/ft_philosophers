/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:25:47 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 15:30:52 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	usage(void)
{
	printf("usage: ./philo number_philosopers time_to_die ");
	printf("time_to_eat time_to_sleep [number_philosopher_must_eat]\n");
}

int	check_args(int ac, char **av)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
		{
			printf("Error: argument should be a positive number.\n");
			return (0);
		}
		i ++;
	}
	return (1);
}

void	init_params(t_params *params, char **av)
{

	params->philo_nbr = ft_atoi(av[1]);
	params->ms_to_die = ft_atoi(av[2]);
	params->ms_to_eat = ft_atoi(av[3]);
	params->ms_to_sleep = ft_atoi(av[4]);
	params->max_eat_times = -1;
	params->ready = 0;
	params->stop = 0;
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_DEATH);
	params->fork = sem_open(SEM_FORK, O_CREAT, 0644, params->philo_nbr);
	params->death = sem_open(SEM_DEATH, O_CREAT, 0644, 1);

}

int	main(int ac, char **av)
{
	t_params	params;

	if (ac < 5 || !check_args(ac, av))
	{
		usage();
		return (0);
	}
	else
	{
		init_params(av, &params);
		if (params.fork == SEM_FAILED || params.death == SEM_FAILED)
		{
			printf("semaphore open error\n");
			return (1);
		}
		if (ac >= 6)
			params.max_eat_times = ft_atoi(av[5]);
		return (solve_philosopher(&params));
	}
}
