/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:56 by zweng             #+#    #+#             */
/*   Updated: 2023/05/04 19:40:21 by zweng            ###   ########.fr       */
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

	lock = shared_lock(NULL);
	pthread_mutex_destroy(lock);
}

void	request_for_eating(t_philo *philo_ptr)
{
	pthread_mutex_t *lock;

	lock = shared_lock(NULL);
	pthread_mutex_lock(&lock);
	if (!philo_ptr)
		return ;
	log_philo_msg(philo_ptr, "requested for eating");
	//ph_go_waiting(philo_ptr);
	if (philo_)
	pthread_mutex_unlock(&lock);
}
