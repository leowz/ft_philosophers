/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:16:46 by zweng             #+#    #+#             */
/*   Updated: 2023/05/16 17:59:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo_msg(t_philo *philo, char *str)
{
	long            timestamp;

	if (!philo || !str)
		return ;
	timestamp = get_timestamp_us() / 1000;
	printf("%ld %d %s\n", timestamp, philo->id, str);
}

void	log_philo_msg_ts(t_philo *philo, char *str, long us)
{
	if (!philo || !str)
		return ;
	printf("%ld %d %s\n", us / 1000, philo->id, str);
}

long	get_timestamp_us(void)
{
	struct timeval  tv;
	long            timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec) * 1000 * 1000 + (tv.tv_usec);
	return (timestamp);
}

void	log_philo_status(t_philo *philo)
{
	if (philo->status == SLEEPING)
		log_philo_msg(philo, "sleeping");
	if (philo->status == EATING)
		log_philo_msg(philo, "eating");
	if (philo->status == THINKING)
		log_philo_msg(philo, "thinking");
	if (philo->status == DEAD)
		log_philo_msg(philo, "deading");
}
