/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:16:46 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 17:53:03 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo_msg(t_philo *philo, char *str)
{
	long            timestamp;

	if (!philo || !str)
		return ;
	timestamp = get_timestamp();
	printf("%ld %d %s\n", timestamp, philo->id, str);
}

long	get_timestamp(void)
{
	struct timeval  tv;
	long            timestamp;

	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
	return (timestamp);
}