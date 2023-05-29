/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:32 by zweng             #+#    #+#             */
/*   Updated: 2023/05/26 16:28:23 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define SEM_FORK ("/FORK")
# define SEM_DEATH ("/DEATH")
# define SEM_ARBITRE ("/ARBITRE")

typedef enum e_status
{
	SLEEPING,
	EATING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_params
{
	int				philo_nbr;
	int				ms_to_die;
	int				ms_to_eat;
	int				ms_to_sleep;
	int				max_eat_times;
	int				ready;
	int				stop;
	sem_t			*fork;
	sem_t			*death;
	sem_t			*arbitrator;
}	t_params;

typedef struct s_philo
{
	unsigned int	id;
	long			last_sleep_begin;
	long			last_think_begin;
	long			last_eat_begin;
	int				eat_times;
	t_status		status;
	t_params		*params;
	struct s_philo	*before;
	struct s_philo	*next;
	pid_t			pid;
}					t_philo;

int				ft_atoi(const char *str);
void			ft_putstr(char const *str);

int				*get_params(int params_get[5]);
void			link_philo(t_philo *current, t_philo *next, t_philo *before);
int				solve_philosopher(t_params *params);
void			log_philo_msg(t_philo *philo, char *str);
long			get_timestamp_us(void);
void			philosopher_go(t_philo *philo);
int				ph_go_dead(t_philo *philo);
int				ph_go_thinking(t_philo *philo, long ts);
int				ph_go_eating(t_philo *philo, long ts);
int				ph_go_sleeping(t_philo *philo, long ts);
void			create_philos(t_philo *f_philo);
void			parent_wait_philos(t_philo *f_philo);
int				need_stop(t_philo *philo);
void			get_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
int				safe_usleep(t_philo *philo, long to_ts);
void			log_philo_status(t_philo *philo);
void			log_philo_msg_ts(t_philo *philo, char *str, long ts);
void			clean_up(t_philo *philo, t_philo *first);
#endif
