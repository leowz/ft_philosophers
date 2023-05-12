/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:56 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 18:44:06 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t *shared_lock(int init)
{
	static pthread_mutex_t lock;
	if (init)
		pthread_mutex_init(&lock, NULL);
	return (&lock);
}

void	destroy_lock()
{
	pthread_mutex_t *lock;

	lock = shared_lock(0);
	pthread_mutex_destroy(lock);
}

int		should_stop(int init, int set_stop)
{
	static int		stop;
	pthread_mutex_t *lock;

	lock = shared_lock(0);
	if (!init && !set_stop)
		return (stop);
	pthread_mutex_lock(lock);
	if (init)
		stop = 0;
	if (set_stop)
		stop = 1;
	pthread_mutex_unlock(lock);
	return (stop);
}

int		request_for_eating(t_philo *philo)
{
	pthread_mutex_t *lock;
	int				ret;

	lock = shared_lock(0);
	if (!philo)
		return (0);
	pthread_mutex_lock(lock);
	//log_philo_msg(philo, "requested for eating");
	if (check_forks(philo))
		ret = 1; // can eat;
	else
		ret = 0; // retry
	pthread_mutex_unlock(lock);
	return (ret);
}
