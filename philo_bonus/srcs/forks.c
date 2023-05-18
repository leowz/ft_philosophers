/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:02:13 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:31:47 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	t_philo 		*philo_left;
	t_philo 		*philo_right;
	pthread_mutex_t *lock;
	int				ret;

	lock = shared_lock(0);
	philo_left = philo->before;
	philo_right = philo->next;
	pthread_mutex_lock(lock);
	if (philo_left->status != EATING && philo_right->status != EATING)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(lock);
	return (ret);
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
	philo->fork_right_hand = NULL;
	if (philo->id == philo_nbr)
		forks[0].owned_by = 0;
	else
		forks[philo->id].owned_by = 0;
}

