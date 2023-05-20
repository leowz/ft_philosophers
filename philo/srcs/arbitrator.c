/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:56 by zweng             #+#    #+#             */
/*   Updated: 2023/05/19 22:40:24 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*pthread_mutex_t	*shared_lock(int init)
{
	static pthread_mutex_t	lock;

	if (init)
		pthread_mutex_init(&lock, NULL);
	return (&lock);
}*/

void	destroy_lock(t_philo *philo)
{
	if (philo)
		pthread_mutex_destroy(&(philo->lock));
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

int	request_for_eating(t_philo *philo)
{
	int				ret;

	if (!philo)
		return (0);
	if (try_take_forks(philo))
		ret = 1;
	else
		ret = 0;
	return (ret);
}
