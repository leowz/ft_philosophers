/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_philosopher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:26:48 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 17:49:17 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_philo *philo, int index, long ts)
{
	philo->id = index + 1;
	philo->eat_count = 0;
	philo->last_sleep_begin = ts;
	philo->last_think_begin = ts;
	philo->last_eat_begin = ts;
	philo->eat_times = 0;
	philo->status = SLEEPING;
	philo->before = NULL;
	philo->next = NULL;
}

void	philosopher_go(t_philo *philo, int *nbr_forks)
{
	int		*pms;
	long	ts;

	pms = get_params(NULL);
	while (!(philo->should_stop))
	{
		ts = get_timestamp_us();
		if (request_for_eating(philo, nbr_forks))
		{
	
			if (ph_go_eating(philo, pms[2], pms[1], ts)
				&& ph_go_sleeping(philo, pms[3], pms[1], get_timestamp_us()))
				continue ;
			else
				break ;
		}
		else
			ph_go_thinking(philo, pms[1], ts);
	}
}

t_philo	*init_philo_table(int philo_nbr)
{
	int		i;
	t_philo	*ptr;
	long	ts;

	i = 0;
	ptr = NULL;
	should_stop(1, 0);
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

int	log_return(char *msg, int ret)
{
	ft_putstr(msg);
	return (ret);
}

int	solve_philosopher(int *params)
{
	t_philo	*first_philo;
	sem_t	*semaphore;
	int		nbr_forks;
	int		should_stop;

	nbr_forks = params[0];
	should_stop = 0;
	semaphore = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (semaphore == SEM_FAILED) 
	{
		printf("semaphore open error\n");
		return (1);
	}
	first_philo = init_philo_table(params[0]);
	if (!first_philo)
		return log_return("Philosopher table initialisation failed!\n", 1);
	create_philos(first_philo, &nbr_forks, &should_stop, semaphore);
	parent_wait_philos(first_philo);
	free(first_philo);
	sem_close(semaphore);
	sem_unlink(SEM_NAME);
	return (0);
}
