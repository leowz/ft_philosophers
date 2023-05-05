/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/04 17:55:43 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int index, int *params)
{
	philo->id = index + 1;
    philo->eat_count = 0;
    philo->time_left = params[1];
    philo->status = THINKING;
	philo->before = NULL;
	philo->next = NULL;
	philo->fork_left = 0;
	philo->fork_right = 0;
}

void    *philosopher_go(void *arg)
{
    t_philo			*philo;
	
	philo = (t_philo *)arg;
	while (philo->status != DEAD)
		request_for_eating(philo);
	return (NULL);
}

t_philo	*init_philo_table(int philo_nbr, int *params)
{
	int		i;
	t_philo	*ptr;

	i = 0;
	ptr = NULL;
	ptr = malloc(sizeof(t_philo) * philo_nbr);
	(void)shared_lock(1);
	if (ptr)
	{
		while (i < philo_nbr)
		{
			init_philo(ptr + i, i, params);
			if (i == 0)
				link_philo(ptr + i, ptr + i + 1, ptr + philo_nbr - 1);
			else if (i == philo_nbr - 1)
				link_philo(ptr + i, ptr, ptr + i - 1);
			else
				link_philo(ptr + i, ptr + i + 1, ptr + i - 1);
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
}

int		solve_philosopher(int *params)
{
	t_philo			*first_philo;
	t_philo			*ptr;
	pthread_mutex_t *lock;

	first_philo = init_philo_table(params[0], params);
	if (!first_philo)
	{
		ft_putstr("Philosopher table initialisation failed!\n");
		return (1);
	}
	ptr = first_philo;
    while (ptr->next != first_philo)
    {
		printf("p create %u\n", ptr->id);
		pthread_create(&(ptr->thread_id), NULL, philosopher_go, ptr);
		ptr = ptr->next;
    }
	ptr = first_philo;
    while (ptr->next != first_philo)
    {
		pthread_join(ptr->thread_id, NULL);
		ptr = ptr->next;
    }
    clean_up(first_philo);
	return (0);
}

