/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:32:29 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int index, long ts)
{
	philo->id = index + 1;
    philo->eat_count = 0;
    philo->last_sleep_begin = ts;
    philo->last_sleep_end = ts;
    philo->last_think_begin = ts;
    philo->last_think_end = ts;
    philo->last_eat_begin = ts;
    philo->last_eat_end = ts;
    philo->eat_times = 0;
    philo->status = SLEEPING;
	philo->before = NULL;
	philo->next = NULL;
	philo->fork_left_hand = NULL;
	philo->fork_right_hand = NULL;
}

int		need_stop(t_philo *philo, int eat_times)
{
	if (!philo)
		return (1);
	if (eat_times > 0 && philo->eat_times >= eat_times)
		return (1);
	else if (should_stop(0, 0))
		return (1);
	else
		return (0);
}

void    *philosopher_go(void *arg)
{
    t_philo	*philo;
	int *pms;
	long ts;
	
	philo = (t_philo *)arg;
	pms = get_params(NULL);
	while (!need_stop(philo, pms[4]))
	{
		ts = get_timestamp_us();
		if (request_for_eating(philo))
		{
			if (ph_go_eating(philo, pms[2], pms[1], ts) &&
					ph_go_sleeping(philo, pms[3], pms[1], get_timestamp_us()))
				continue ;
			else
				break ;
		}
		else
			ph_go_thinking(philo, pms[1], ts);
	}
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
	(void)shared_lock(1);
	(void)get_forks(philo_nbr);
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

void	clean_up(t_philo *philo)
{
	free(philo);
	destroy_lock();
	destroy_forks();
}


void	create_threads(t_philo *f_philo)
{
	t_philo			*ptr;

	if (!f_philo)
		return ;
	ptr = f_philo;
    while (1)
    {
		pthread_create(&(ptr->thread_id), NULL, philosopher_go, ptr);
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
    }
}

void	join_threads(t_philo *f_philo)
{
	t_philo			*ptr;

	if (!f_philo)
		return ;
	ptr = f_philo;
    while (1)
    {
		pthread_join(ptr->thread_id, NULL);
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
    }
}

int		solve_philosopher(int *params)
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
    clean_up(first_philo);
	return (0);
}

