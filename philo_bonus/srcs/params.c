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

void	link_philo(t_philo *current, t_philo *next, t_philo *before)
{
	if (current && next)
		current->next = next;
	if (current && before)
		current->before = before;
}
