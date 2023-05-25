/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/20 09:36:49 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int index, long ts, t_params *params)
{
	philo->params = params;
	philo->id = index + 1;
	philo->last_sleep_begin = ts;
	philo->last_think_begin = ts;
	philo->last_eat_begin = ts;
	philo->backoff = 0;
	philo->ready = 0;
	philo->eat_times = 0;
	philo->fork	= -1;
	philo->status = SLEEPING;
	philo->before = NULL;
	philo->next = NULL;
	pthread_mutex_init(&(philo->lock), NULL);
}

void	*philosopher_go(void *arg)
{
	t_philo		*philo;
	t_params	*pms;
	long		ts;

	philo = (t_philo *)arg;
	pms = philo->params;
	while (!pms->ready)
		continue ;
	while (1)
	{
		ts = get_timestamp_us();
		if (request_for_eating(philo))
		{
			if (ph_go_eating(philo, ts) &&
					ph_go_sleeping(philo,  get_timestamp_us()))
				continue ;
			else
				break ;
		}
		if (!ph_go_thinking(philo,  ts))
			break ;
	}
	return (NULL);
}

t_philo	*init_philo_table(t_params *params)
{
	int		i;
	int		philo_nbr;
	t_philo	*ptr;

	i = 0;
	ptr = NULL;
	philo_nbr = params->philo_nbr;
	ptr = malloc(sizeof(t_philo) * philo_nbr);
	if (ptr)
	{
		while (i < philo_nbr)
		{
			init_philo(ptr + i, i, get_timestamp_us(), params);
			link_philo(ptr + i, ptr + ((i + 1) % philo_nbr),
				ptr + ((i - 1 + philo_nbr) % philo_nbr));
			i++;
		}
	}
	else
		printf("malloc failed\n");
	return (ptr);
}

int	solve_philosopher(t_params *params)
{
	t_philo			*first_philo;

	first_philo = init_philo_table(params);
	if (!first_philo)
	{
		ft_putstr("Philosopher table initialisation failed!\n");
		return (1);
	}
	create_threads(first_philo);
	join_threads(first_philo);
	free(first_philo);
	return (0);
}
