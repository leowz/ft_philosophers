/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:01:21 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 14:20:00 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_usleep(t_philo *philo, long to_ts)
{
	long		current_ts;
	long		cd;
	long		interval;
	t_params	*params;

	interval = 101;
	params = philo->params;
	while (1)
	{
		current_ts = get_timestamp_us();
		cd = to_ts - current_ts;
		if (cd < 0 || (current_ts - philo->last_eat_begin
			>= 1000 * params->ms_to_die))
			break ;
		if (cd > 0 && cd < interval)
		{
			usleep(cd);
			break ;
		}
		else
			usleep(interval);
	}
	return (1);
}
