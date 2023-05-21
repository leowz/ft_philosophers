/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:44:51 by zweng             #+#    #+#             */
/*   Updated: 2023/05/19 23:21:03 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	link_philo(t_philo *current, t_philo *next, t_philo *before)
{
	if (current && next)
		current->next = next;
	if (current && before)
		current->before = before;
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
		pthread_mutex_destroy(&(ptr->lock));
		if (ptr == f_philo)
			break ;
	}
}

int	should_stop(int init, int set_stop)
{
	static int		stop;

	if (!init && !set_stop)
		return (stop);
	if (init)
		stop = 0;
	if (set_stop)
		stop = 1;
	return (stop);
}

int	need_stop(t_philo *philo, unsigned int eat_times)
{
	if (!philo)
		return (1);
	if (eat_times > 0 && philo->eat_times >= eat_times)
	{
		// printf("%d need to stop %d\n", philo->id, philo->eat_times);
		return (1);
	}
	else if (should_stop(0, 0))
		return (1);
	else
		return (0);
}
