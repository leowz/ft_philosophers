/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:44:51 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 16:26:26 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	*get_params(int params_get[5])
{
	static int	params[5];

	if (params_get)
	{
		params[0] = params_get[0];
		params[1] = params_get[1];
		params[2] = params_get[2];
		params[3] = params_get[3];
		params[4] = params_get[4];
	}
	return (params);
}

void	link_philo(t_philo *current, t_philo *next, t_philo *before)
{
	if (current && next)
		current->next = next;
	if (current && before)
		current->before = before;
}
