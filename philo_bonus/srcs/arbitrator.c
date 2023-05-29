/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:09:56 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 17:19:55 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	need_stop(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	if (!philo)
		return (1);
	if (params->max_eat_times > 0 && philo->eat_times >= params->max_eat_times)
		return (1);
	else if (params->stop)
		return (1);
	else
		return (0);
}

void	get_forks(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	sem_wait(params->arbitrator);
	sem_wait(params->fork);
	log_philo_msg(philo, "has taken a fork");
	sem_wait(params->fork);
	log_philo_msg(philo, "has taken a fork");
	sem_post(params->arbitrator);
}

void	drop_forks(t_philo *philo)
{
	t_params	*params;

	params = philo->params;
	sem_post(params->fork);
	sem_post(params->fork);
}
