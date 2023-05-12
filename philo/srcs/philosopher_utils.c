/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:28 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 18:32:13 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_go_dead(t_philo *philo)
{
	if (!philo)
		return (0);
	philo->status = DEAD;
	log_philo_msg(philo, "died");
	return (1);
}

int	ph_go_thinking(t_philo *philo)
{
	int				*params;
	unsigned int	time_to_think;
	
	if (!philo)
		return (0);
	params = get_params(NULL);
	philo->status = THINKING;
	log_philo_msg(philo, "is thinking");
	time_to_think = (params[1] - 5) / 2; 
	return (safe_msleep(philo, time_to_think));
}

int	ph_go_eating(t_philo *philo)
{
	int	*params;
	
	if (!philo)
		return (0);
	params = get_params(NULL);
	philo->status = EATING;
	log_philo_msg(philo, "is eating");
	philo->time_left += params[1];
	if (safe_msleep(philo, params[2]))
	{
		philo_drop_forks(philo);
		return (1);
	}
	return (0);
}

int	ph_go_sleeping(t_philo *philo)
{
	int	*params;
	
	params = get_params(NULL);
	if (!philo)
		return (0);
	philo->status = SLEEPING;
	log_philo_msg(philo, "is sleeping");
	return (safe_msleep(philo, params[3]));
}
