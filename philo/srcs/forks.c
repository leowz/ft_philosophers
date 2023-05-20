/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:02:13 by zweng             #+#    #+#             */
/*   Updated: 2023/05/19 23:36:51 by zweng            ###   ########.fr       */
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

int	try_take_forks(t_philo *philo)
{
	int		ret;

	if (take_forks(philo))
		ret = 1;
	else
		ret = 0;
	return (ret);
}
