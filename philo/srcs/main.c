/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:25:47 by zweng             #+#    #+#             */
/*   Updated: 2023/04/28 16:43:25 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage()
{
	printf("usage: ./philo number_philosopers time_to_die 
			time_to_eat time_to_sleep [number_philosopher_must_eat]");
}

int	main(int ac, char **av)
{
	if (ac <= 4) {
		usage();
	} else {

	}
    return (0);
}
