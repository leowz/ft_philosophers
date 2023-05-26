/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 16:27:04 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int index, long ts, t_params *params)
{
	philo->params = params;
	philo->id = index + 1;
	philo->last_sleep_begin = ts;
	philo->last_think_begin = ts;
	philo->last_eat_begin = ts;
	philo->eat_times = 0;
	philo->status = SLEEPING;
	philo->before = NULL;
	philo->next = NULL;
}

void	philosopher_go(t_philo *philo)
{
	while (1)
	{
		if (ph_go_thinking(philo, get_timestamp_us())
			&& ph_go_eating(philo, get_timestamp_us())
			&& ph_go_sleeping(philo, get_timestamp_us()))
			continue ;
		else
			break ;
	}
}

t_philo	*init_philo_table(t_params *params)
{
	int		i;
	t_philo	*ptr;
	int		philo_nbr;
	long	ts;

	i = 0;
	ptr = NULL;
	philo_nbr = params->philo_nbr;
	ptr = malloc(sizeof(t_philo) * philo_nbr);
	ts = get_timestamp_us();
	if (ptr)
	{
		while (i < philo_nbr)
		{
			init_philo(ptr + i, i, ts, params);
			link_philo(ptr + i, ptr + ((i + 1) % philo_nbr),
				ptr + ((i - 1 + philo_nbr) % philo_nbr));
			i++;
		}
	}
	else
		printf("malloc failed\n");
	return (ptr);
}

int	log_return(char *msg, int ret)
{
	ft_putstr(msg);
	return (ret);
}

int	solve_philosopher(t_params *params)
{
	t_philo	*first_philo;

	first_philo = init_philo_table(params);
	if (!first_philo)
		return (log_return("Philosopher table initialisation failed!\n", 1));
	create_philos(first_philo);
	parent_wait_philos(first_philo);
	sem_close(first_philo->params->death);
	sem_close(first_philo->params->fork);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_FORK);
	free(first_philo);
	return (0);
}
