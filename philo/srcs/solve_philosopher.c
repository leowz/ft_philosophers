/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/01 16:27:02 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int index, int *params)
{
	philo->
}

int		solve_philosopher(int *params)
{
	int		i;
	t_philo	*philo_arr;

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
	return (0);
}

