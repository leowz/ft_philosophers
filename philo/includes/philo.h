/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:26:14 by zweng             #+#    #+#             */
/*   Updated: 2023/05/03 14:54:32 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum	e_status
{
	SLEEP,
	EAT,
	THINK,
	DIED
}				t_status;

typedef struct	s_philo
{
	int			id;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eat_count;
	t_status	status;
}				t_philo;


int				ft_atoi(const char *str);
int             solve_philosopher(int *params);

#endif
