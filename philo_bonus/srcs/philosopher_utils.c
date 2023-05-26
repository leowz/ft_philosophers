/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:28 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 17:48:15 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ph_go_dead(t_philo *philo, long ts)
{
	if (!philo)
		return (0);
	philo->status = DEAD;
	log_philo_msg_ts(philo, "died", ts);
	sem_wait(philo->params->death);
	philo->params->stop = 1;
	sem_post(philo->params->death);
	return (0);
}

int	ph_go_thinking(t_philo *philo, long ts)
{
	int		us;
	int		t_to_die;

	t_to_die = philo->params->ms_to_die;
	if (philo->status != THINKING)
	{
		philo->status = THINKING;
		log_philo_msg_ts(philo, "is thinking", ts);
	}
	us = 11;
	philo->last_think_begin = ts;
	usleep(us);
	if (philo->last_think_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts));
	return (1);
}

int	ph_go_eating(t_philo *philo, int ms, long ts)
{
	int		us;
	int		t_to_die;

	t_to_die = philo->params->ms_to_die;
	philo->status = EATING;
	philo->eat_times++;
	philo->last_eat_begin = ts;
	log_philo_msg_ts(philo, "is eating", ts);
	us = philo->params->ms_to_eat * 1000;
	safe_usleep(philo, ts + us);
	if (philo->last_eat_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts));
	return (1);
}

int	ph_go_sleeping(t_philo *philo, long ts)
{
	int		us;
	int		t_to_die;

	t_to_die = philo->params->ms_to_die;
	philo->status = SLEEPING;
	philo->last_sleep_begin = ts;
	log_philo_msg_ts(philo, "is sleeping", ts);
	us = philo->params->ms_to_sleep * 1000;
	safe_usleep(philo, ts + us);
	if (philo->last_sleep_begin + us - philo->last_eat_begin > t_to_die * 1000)
		return (ph_go_dead(philo, ts));
	return (1);
}
