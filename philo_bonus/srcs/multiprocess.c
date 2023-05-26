/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:42:31 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 16:25:57 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philos(t_philo *f_philo)
{
	t_philo			*ptr;
	pid_t			pid;

	ptr = f_philo;
	while (ptr)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("create philo %d failed\n", ptr->id);
			break ;
		}
		else if (pid == 0)
		{
			philosopher_go(ptr);
			exit(0);
		}
		ptr->pid = pid;
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
	}
}

void	parent_wait_philos(t_philo *f_philo)
{
	t_philo	*ptr;
	pid_t	pid;
	int		status;

	ptr = f_philo;
	while (ptr)
	{
		pid = waitpid(ptr->pid, &status, 0);
		if (pid == -1)
			printf("Error when waiting for child pcs.\n");
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
	}
}
