/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:28 by zweng             #+#    #+#             */
/*   Updated: 2023/05/20 00:34:35 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_go_dead(t_philo *philo, long ts)
{
	if (!philo)
		return (0);
	philo->status = DEAD;
	log_philo_msg_ts(philo, "died", ts);
	if (!should_stop(0, 0))
		should_stop(0, 1);
	return (0);
}

int	ph_go_thinking(t_philo *philo, int t_to_die, long ts)
{
	int		us;

	if (philo->status != THINKING)
	{
		philo->status = THINKING;
		log_philo_msg_ts(philo, "is thinking", ts);
	}
	us = 97;
	philo->last_think_begin = ts;
	usleep(us);
	if (philo->last_think_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts + us));
	return (1);
}

int	ph_go_eating(t_philo *philo, int ms, int t_to_die, long ts)
{
	int		us;

	philo->status = EATING;
	philo->eat_times++;
	philo->last_eat_begin = ts;
	log_philo_msg_ts(philo, "is eating", ts);
	us = ms * 1000;
	safe_usleep(philo, ts + us);
	drop_forks(philo);
	if (philo->last_eat_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts + us));
	return (1);
}

int	ph_go_sleeping(t_philo *philo, int ms, int t_to_die, long ts)
{
	int		us;

	philo->status = SLEEPING;
	philo->last_sleep_begin = ts;
	log_philo_msg_ts(philo, "is sleeping", ts);
	us = ms * 1000;
	safe_usleep(philo, ts + us);
	if (philo->last_sleep_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts + us));
	return (1);
}
