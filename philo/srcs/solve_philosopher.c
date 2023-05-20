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

void	init_philo(t_philo *philo, int index, long ts)
{
	philo->id = index + 1;
	philo->last_sleep_begin = ts;
	philo->last_think_begin = ts;
	philo->last_eat_begin = ts;
	philo->eat_times = 0;
	philo->fork	= -1;
	philo->status = SLEEPING;
	philo->before = NULL;
	philo->next = NULL;
	pthread_mutex_init(&(philo->lock), NULL);
}

void	*philosopher_go(void *arg)
{
	t_philo	*philo;
	int		*pms;
	long	ts;

	philo = (t_philo *)arg;
	pms = get_params(NULL);
	log_philo_msg_ts(philo, "created", get_timestamp_us());
	/*while (!need_stop(philo, pms[4]))
	{
		ts = get_timestamp_us();
		if (request_for_eating(philo))
		{
			if (ph_go_eating(philo, pms[2], pms[1], ts)
				&& ph_go_sleeping(philo, pms[3], pms[1], get_timestamp_us()))
				continue ;
			else
				break ;
		}
		else
			ph_go_thinking(philo, pms[1], ts);
	}*/
	return (NULL);
}

t_philo	*init_philo_table(int philo_nbr)
{
	int		i;
	t_philo	*ptr;
	long	ts;

	i = 0;
	ptr = NULL;
	ptr = malloc(sizeof(t_philo) * philo_nbr);
	ts = get_timestamp_us();
	if (ptr)
	{
		while (i < philo_nbr)
		{
			init_philo(ptr + i, i, ts);
			link_philo(ptr + i, ptr + ((i + 1) % philo_nbr),
				ptr + ((i - 1 + philo_nbr) % philo_nbr));
			i++;
		}
	}
	else
		printf("malloc failed\n");
	return (ptr);
}

int	solve_philosopher(int *params)
{
	t_philo			*first_philo;

	first_philo = init_philo_table(params[0]);
	should_stop(1, 0);
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
