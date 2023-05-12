/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 18:44:29 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, int index, int *params)
{
	//printf("init philo: %d\n", index);
	philo->id = index + 1;
    philo->eat_count = 0;
    philo->time_left = params[1];
    philo->status = THINKING;
	philo->before = NULL;
	philo->next = NULL;
	philo->fork_left_hand = NULL;
	philo->fork_right_hand = NULL;
}

void	*timer_go(void *arg)
{
    t_philo	*philo;
	
	philo = (t_philo *)arg;
	//printf("%d timer start %lu\n", philo->id, get_timestamp());
	while (philo->time_left > 0)
	{
		usleep(1000);
		philo->time_left--;
	}
	ph_go_dead(philo);
	return (NULL);
}

void    *philosopher_go(void *arg)
{
    t_philo	*philo;
	int		can_eat;
	
	philo = (t_philo *)arg;
	//printf("%d philo created %lu\n", philo->id, get_timestamp());
	pthread_create(&(philo->thread_timer_id), NULL, timer_go, philo);
	while (1)
	{
		can_eat = request_for_eating(philo);
		if (!can_eat)
		{
			if (!ph_go_thinking(philo))
				break ;
			continue ;
		}
		if (!ph_go_eating(philo))
			break ;
		if (!ph_go_sleeping(philo))
			break ;
	}
	pthread_join(philo->thread_timer_id, NULL);
	return (NULL);
}

t_philo	*init_philo_table(int philo_nbr, int *params)
{
	int		i;
	t_philo	*ptr;

	i = 0;
	ptr = NULL;
	//printf("philo_nbr %d\n", philo_nbr);
	ptr = malloc(sizeof(t_philo) * philo_nbr);
	(void)shared_lock(1);
	(void)get_forks(philo_nbr);
	if (ptr)
	{
		while (i < philo_nbr)
		{
			init_philo(ptr + i, i, params);
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
		//printf("p create %u\n", ptr->id);
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

	first_philo = init_philo_table(params[0], params);
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

