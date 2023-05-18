/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:01:21 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:35:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_usleep(t_philo *philo, long to_ts)
{
	long	current_ts;
	long	cd;
	long	interval;

	(void)philo;
	interval = 101;
	while (1)
	{
		current_ts = get_timestamp_us();
		cd = to_ts - current_ts;
		if (cd > 0)
			usleep(interval);
		else
			break ;
	}
	return (1);
}
