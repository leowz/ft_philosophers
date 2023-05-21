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

void	destroy_lock(t_philo *philo)
{
	if (philo)
		pthread_mutex_destroy(&(philo->lock));
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
