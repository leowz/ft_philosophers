/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 18:01:21 by zweng             #+#    #+#             */
/*   Updated: 2023/05/17 17:16:01 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	count_down(t_philo *philo, long live_us, long current_ts, long last_ts)
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
	return (cd);
}

int	safe_usleep(t_philo *philo, long us, long last_ts, int ms_to_die)
{
	long	ts;
	long	cd;
	long	ttl;

//	printf("enter usleep %d, us(%ld), last_ts(%ld), mtd(%d)\n", philo->id, us, last_ts, ms_to_die);
	while (1)
	{
		ts = get_timestamp_us();
		cd = count_down(philo, us, ts, last_ts);
		ttl = time_to_live(philo, ms_to_die, ts);
		if (cd > 0 && ttl > 0)
			usleep(103);
		else
			break ;
	}
	//printf("break usleep\n");
	//printf("%d time to live: %ld\n", philo->id, ttl);
	if (ttl <= 0)
	{
		ph_go_dead(philo, ts);
		if (!should_stop(0, 0))
			should_stop(0 , 1);
		return (0);
	}
	else
		return (1);
}
