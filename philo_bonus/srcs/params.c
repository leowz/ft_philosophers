/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:44:51 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 17:50:56 by zweng            ###   ########.fr       */
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
			printf("exit status %d\n", exit_status);
		}
		ptr = ptr->next;
		if (ptr == f_philo)
			break ;
	}
}
