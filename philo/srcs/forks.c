/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:02:13 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 14:18:55 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_forks(t_philo *philo)
{
	t_philo	*philo_right;

	philo_right = philo->next;
	if (philo && philo_right && philo != philo_right)
	{
		pthread_mutex_lock(&(philo->lock));
		pthread_mutex_lock(&(philo_right->lock));
		philo->fork = NOT_TAKEN;
		philo_right->fork = NOT_TAKEN;
		pthread_mutex_unlock(&(philo->lock));
		pthread_mutex_unlock(&(philo_right->lock));
	}
}

static int	take_forks(t_philo *philo)
{
	t_philo	*philo_right;
	int		ret;

	ret = 0;
	philo_right = philo->next;
	if (philo && philo_right && philo != philo_right)
	{
		pthread_mutex_lock(&(philo->lock));
		pthread_mutex_lock(&(philo_right->lock));
		if (philo->fork == NOT_TAKEN && philo_right->fork == NOT_TAKEN)
		{
			philo->fork = philo->id;
			philo_right->fork = philo->id;
			ret = 1;
		}
		pthread_mutex_unlock(&(philo->lock));
		pthread_mutex_unlock(&(philo_right->lock));
	}
	return (ret);
}

int	should_take_fork(t_philo *philo)
{
	t_philo	*philo_right;
	t_philo	*philo_left;

	philo_left = philo->before;
	philo_right = philo->next;
	if (philo_left->status == THINKING
		&& philo_left->last_eat_begin < philo->last_eat_begin)
		return (0);
	if (philo_right->status == THINKING
		&& philo_right->last_eat_begin < philo->last_eat_begin)
		return (0);
	return (1);
}

int	try_take_forks(t_philo *philo)
{
	int		ret;

	if (should_take_fork(philo) && take_forks(philo))
		ret = 1;
	else
		ret = 0;
	return (ret);
}
