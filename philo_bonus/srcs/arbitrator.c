/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:56 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 17:19:55 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	check_forks(t_philo *philo, int *nbr_forks)
{
	int				ret;

	sem_wait(philo->semaphore);
	if (*nbr_forks >= 2)
	{	
		*nbr_forks -= 2;	
		ret = 1;
	}
	else
		ret = 0;
	sem_post(philo->semaphore);
	return (ret);
}

int	request_for_eating(t_philo *philo, int *nbr_forks)
{
	int				ret;

	if (!philo)
		return (0);
	if (check_forks(philo, nbr_forks))
		ret = 1;
	else
		ret = 0;
	return (ret);
}
