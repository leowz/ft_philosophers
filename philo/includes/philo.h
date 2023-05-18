/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:26:14 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 15:03:40 by zweng            ###   ########.fr       */
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

typedef enum e_status
{
	SLEEPING,
	EATING,
	THINKING,
	DEAD
}	t_status;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	eat_count;
	long			last_sleep_begin;
	long			last_think_begin;
	long			last_eat_begin;
	int				eat_times;
	t_status		status;
	struct s_philo	*before;
	struct s_philo	*next;
	pthread_t		thread_id;
	pthread_t		thread_timer_id;
}	t_philo;

int				ft_atoi(const char *str);
void			ft_putstr(char const *str);

int				*get_params(int params_get[5]);
void			link_philo(t_philo *current, t_philo *next, t_philo *before);
int				solve_philosopher(int *params);
long			get_timestamp_us(void);
void			*philosopher_go(void *arg);
int				request_for_eating(t_philo *philo_ptr);
void			create_threads(t_philo *f_philo);
void			join_threads(t_philo *f_philo);
int				need_stop(t_philo *philo, int eat_times);
int				ph_go_dead(t_philo *philo, long ts);
int				ph_go_thinking(t_philo *philo, int ttd, long ts);
int				ph_go_eating(t_philo *philo, int ms, int ttd, long ts);
int				ph_go_sleeping(t_philo *philo, int ms, int ttd, long ts);
pthread_mutex_t	*shared_lock(int init);
void			destroy_lock(void);
int				check_forks(t_philo *philo);
int				safe_usleep(t_philo *philo, long to_ts);
int				should_stop(int init, int set_stop);
void			log_philo_msg_ts(t_philo *philo, char *str, long ts);
#endif
