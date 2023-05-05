/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:16:46 by zweng             #+#    #+#             */
/*   Updated: 2023/05/04 14:22:29 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_philo_msg(t_philo *philo, char *str)
{
	struct timeval  tv;
	long            timestamp;

	if (!philo || !str)
		return ;
	gettimeofday(&tv, NULL);
	timestamp = (tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
	printf("%ld %d %s\n", timestamp, philo->id, str);
}
