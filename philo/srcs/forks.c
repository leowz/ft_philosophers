/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:02:13 by zweng             #+#    #+#             */
/*   Updated: 2023/05/10 18:48:02 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*get_forks(int nbr)
{
	static t_fork	*forks;
	int				i;
	if (nbr > 0)
	{
		i = 0;
		forks = malloc(sizeof(t_fork) * nbr);
		while (i < nbr && forks)
		{
			forks[i].owned_by = 0;
			forks[i].on_the_left_of = i + 1;
			i++;
		}
	}
	return (forks);
}

void	destroy_forks(void)
{
	t_fork	*forks;

	forks = get_forks(0);
	free(forks);
}

int		check_forks(t_philo *philo)
{
	t_philo *philo_left;
	t_philo *philo_right;

	philo_left = philo->before;
	philo_right = philo->next;
	if (philo_left->status != EATING && philo_right->status != EATING)
		return (1);
	else
		return (0);
		
/*	if (!philo_left->fork_right_hand && !philo_right->fork_left_hand)
		return (1);
	return (0);*/
}

void	philo_take_forks(t_philo *philo)
{
	t_fork			*forks;
	int				*params;
	unsigned int	philo_nbr;

	forks = get_forks(0);
	params = get_params(0);
	philo_nbr = params[0];
	philo->fork_left_hand = forks + philo->id - 1;
	forks[philo->id - 1].owned_by = philo->id;
	//log_philo_msg(philo, "has taken a fork");
	if (philo->id == philo_nbr)
	{
		philo->fork_right_hand = forks;
		forks[0].owned_by = philo->id;
	}
	else
	{
		philo->fork_right_hand = forks + philo->id;
		forks[philo->id].owned_by = philo->id;
	}
	//log_philo_msg(philo, "has taken a fork");
}

void	philo_drop_forks(t_philo *philo)
{
	t_fork			*forks;
	int				*params;
	unsigned int	philo_nbr;

	forks = get_forks(0);
	params = get_params(0);
	philo_nbr = params[0];
	philo->fork_left_hand = NULL;
	forks[philo->id - 1].owned_by = 0;
//	log_philo_msg(philo, "has dropped a fork");
	philo->fork_right_hand = NULL;
	if (philo->id == philo_nbr)
		forks[0].owned_by = 0;
	else
		forks[philo->id].owned_by = 0;
//	log_philo_msg(philo, "has dropped a fork");
}

