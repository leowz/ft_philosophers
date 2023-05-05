/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:25:47 by zweng             #+#    #+#             */
/*   Updated: 2023/05/04 14:57:24 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage()
{
	printf("usage: ./philo number_philosopers time_to_die ");
	printf("time_to_eat time_to_sleep [number_philosopher_must_eat]");
}

int		check_args(int ac, char **av)
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

int		main(int ac, char **av)
{
	int params[5];

	if (ac < 5 || !check_args(ac, av))
	{
		usage();
    	return (0);
	} 
	else
	{
		memset(params, -1, sizeof(int) * 5);
		params[0] = ft_atoi(av[1]);
		params[1] = ft_atoi(av[2]);
		params[2] = ft_atoi(av[3]);
		params[3] = ft_atoi(av[4]);
		if (ac >= 6)
			params[4] = ft_atoi(av[5]);
		(void)get_params(params);
		return (solve_philosopher(params));
	}
}
