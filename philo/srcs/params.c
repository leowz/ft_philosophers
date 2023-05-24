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
		pthread_create(&(ptr->thread_id), NULL, &philosopher_go, ptr);
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
	}
	ptr = f_philo;
	ptr->params->ready = 1;
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
	pthread_mutex_destroy(&(ptr->params->death));
}

int	need_stop(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	if (!philo)
		return (1);
	if (philo->eat_times >= params->max_eat_times)
		return (1);
	else if (params->stop)
		return (1);
	else
		return (0);
}
