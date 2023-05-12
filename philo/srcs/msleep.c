/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:01:21 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 19:00:26 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_msleep(t_philo *philo, unsigned int ms)
{
	if (should_stop(0, 0))
	{
	
		printf("should stop %d\n", should_stop(0, 0));
		return (0);
	}
	while (ms && philo->time_left > 0)
	{
		usleep(1000);
		ms--;
	}
	if (ms <= 0)
		return (1);
	else
	{
		if (!should_stop(0, 0))
			should_stop(0, 1);
		return (0);
	}
}
