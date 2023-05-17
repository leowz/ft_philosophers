/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:28 by zweng             #+#    #+#             */
/*   Updated: 2023/05/17 17:03:40 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_go_dead(t_philo *philo, long ts)
{
	if (!philo)
		return (0);
	philo->status = DEAD;
	log_philo_msg_ts(philo, "died", ts);
	return (1);
}

int	ph_go_thinking(t_philo *philo, int t_to_die, long ts)
{
	int		ret;

	if (philo->status != THINKING)
	{
		philo->status = THINKING;
		log_philo_msg_ts(philo, "is thinking", ts);
	}
	philo->last_think_begin = ts;
	ret = safe_usleep(philo, 37, ts, t_to_die);
	philo->last_think_end = get_timestamp_us();
	return (ret);
}

int	ph_go_eating(t_philo *philo, int ms, int t_to_die, long ts)
{
	int		ret;
	long	last;

	if (philo->status == THINKING)
		last = philo->last_think_end;
	else
		last = philo->last_sleep_end;
	philo->status = EATING;
	philo->eat_times++;
	philo->last_eat_begin = ts;
	log_philo_msg_ts(philo, "is eating", ts);
	ret = safe_usleep(philo, ms * 1000, last, t_to_die);
	philo->last_eat_end = get_timestamp_us();
	return (ret);
}

int	ph_go_sleeping(t_philo *philo, int ms, int t_to_die, long ts)
{
	int		ret;
	long	last;

	philo->status = SLEEPING;
	philo->last_sleep_begin = ts;
	last = philo->last_eat_end;
	log_philo_msg_ts(philo, "is sleeping", ts);
	ret = safe_usleep(philo, ms * 1000, last, t_to_die);
	philo->last_eat_end = get_timestamp_us();
	return (ret);
}
