/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:42:31 by zweng             #+#    #+#             */
/*   Updated: 2023/05/22 13:42:47 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_philos(t_philo *f_philo, int *nbr_forks, int *should_stop, 
		sem_t *semaphore)
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
			ptr->semaphore = semaphore;
			ptr->should_stop = should_stop;
			philosopher_go(ptr, nbr_forks);
			exit(0);
		}
		// master process logic
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
	int		exit_status;

	ptr = f_philo;
	while (ptr)
	{
		pid = waitpid(ptr->pid, &status, 0);
		if (pid == -1)
			printf("Error when waiting for child pcs.\n");
		else
		{
			exit_status = WEXITSTATUS(status);
			printf("%d exit status %d\n", pid, exit_status);
		}
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
	}
}

