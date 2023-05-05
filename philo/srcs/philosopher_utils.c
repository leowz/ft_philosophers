/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:28:28 by zweng             #+#    #+#             */
/*   Updated: 2023/05/04 17:12:59 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_go_dead(t_philo *philo)
{
	if (!philo)
		return ;
	philo->status = DEAD;
	log_philo_msg(philo, "died");
}

void	ph_go_waiting(t_philo *philo)
{
	if (!philo)
		return ;
	philo->status = THINKING;
	log_philo_msg(philo, "thinking");
	usleep(1000);
}

void	ph_go_eating(t_philo *philo)
{
	int	*params;
	
	params = get_params(NULL);
	if (!philo)
		return ;
	philo->status = EATING;
	log_philo_msg(philo, "is eating");
	usleep(1000 * params[2]);
	ph_go_sleeping(philo);
}

void	ph_go_sleeping(t_philo *philo)
{
	int	*params;
	
	params = get_params(NULL);
	if (!philo)
		return ;
	philo->status = SLEEPING;
	log_philo_msg(philo, "is sleeping");
	usleep(1000 * params[3]);
}
