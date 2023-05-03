/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/03 16:23:04 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int index, int *params)
{
	philo->id = index + 1;
    philo->time_to_die = params[0];
    philo->time_to_eat = params[0];
    philo->time_to_sleep = params[0];
    philo->eat_count = 0;
    philo->status = THINK;
}

int		solve_philosopher(int *params)
{
	int             i;
	t_philo	        *philo_arr;
    struct timeval  time;

	i = 0;
	philo_arr = malloc(sizeof(t_philo) * params[0]);
	if (!philo_arr)
	{
		printf("malloc philo failed!\n");
		return (1);
	}
	while (i < params[0])
	{
		init_philo(philo_arr, i, params);
		i++;
	}
    gettimeofday(&time, NULL);
    free(philo_arr);
	return (0);
}

