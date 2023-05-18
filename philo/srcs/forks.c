/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:02:13 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:58:43 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_forks(t_philo *philo)
{
	t_philo			*philo_left;
	t_philo			*philo_right;
	pthread_mutex_t	*lock;
	int				ret;

	lock = shared_lock(0);
	philo_left = philo->before;
	philo_right = philo->next;
	pthread_mutex_lock(lock);
	if (philo_left->status != EATING && philo_right->status != EATING)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(lock);
	return (ret);
}
