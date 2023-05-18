/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:01:21 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:32:04 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	time_to_live(t_philo *philo, long ms_to_die, long ts)
{
	long	last_current_diff;	
	long	to_live;

	if (!philo)
		return (0l);
	last_current_diff = ts - philo->last_eat_begin;
	to_live = (ms_to_die * 1000 - last_current_diff);
	//printf("%ld %d to live %ld\n",get_timestamp(), philo->id, to_live);
	return (to_live);
}

/*long	count_down(t_philo *philo, long current_ts, long to_ts, long last_ts)
{
	long	last_current_diff;	
	long	cd;

	last_current_diff = current_ts - last_ts;
	cd =  (live_us - last_current_diff);
	if (0)
	{
		log_philo_status(philo);
	//	printf("%d count down: %ld(%ld)\n", philo->id, cd, us);
	//	printf("ts %ld, uts %ld\n", ts, last_ts);
	}
	return (to_ts - current_ts);
}*/

int	safe_usleep(t_philo *philo, long to_ts)
{
	long	current_ts;
	long	cd;
	long	interval;

//	printf("enter usleep %d, us(%ld), last_ts(%ld), mtd(%d)\n", philo->id, us, last_ts, ms_to_die);

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
	//printf("break usleep\n");
	//printf("%d time to live: %ld\n", philo->id, ttl);
	return (1);
}
