/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <zweng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:17:32 by zweng             #+#    #+#             */
/*   Updated: 2023/05/18 14:17:58 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum		e_status
{
	SLEEPING,
	EATING,
	THINKING,
	DEAD
}					t_status;

typedef struct		s_fork
{
	unsigned int	owned_by;
	unsigned int	on_the_left_of;
}					t_fork;

typedef struct		s_philo
{
	unsigned int	id;
	unsigned int	eat_count;
	long			last_sleep_begin;
	long			last_sleep_end;
	long			last_think_begin;
	long			last_think_end;
	long			last_eat_begin;
	long			last_eat_end;
	int				eat_times;
	t_fork			*fork_left_hand;
	t_fork			*fork_right_hand;
	t_status		status;
	struct s_philo	*before;
	struct s_philo	*next;
    pthread_t   	thread_id;
    pthread_t   	thread_timer_id;
}					t_philo;

int				ft_atoi(const char *str);
void			ft_putstr(char const *str);

int				*get_params(int params_get[5]);
void			link_philo(t_philo *current, t_philo *next, t_philo *before);
int             solve_philosopher(int *params);
void			log_philo_msg(t_philo *philo, char *str);
long			get_timestamp_us(void);
int				request_for_eating(t_philo *philo_ptr);
int				ph_go_dead(t_philo *philo, long ts);
int				ph_go_thinking(t_philo *philo, int ttd, long ts);
int				ph_go_eating(t_philo *philo, int ms, int ttd, long ts);
int				ph_go_sleeping(t_philo *philo, int ms, int ttd, long ts);
pthread_mutex_t *shared_lock(int init);
void    		destroy_lock();
t_fork  		*get_forks(int nbr);
int     		check_forks(t_philo *philo);
void    		philo_take_forks(t_philo *philo);
void    		philo_drop_forks(t_philo *philo);
void    		destroy_forks(void);
int				safe_usleep(t_philo *philo, long to_ts);
int				should_stop(int init, int set_stop);
void            log_philo_status(t_philo *philo);
void			log_philo_msg_ts(t_philo *philo, char *str, long ts);

#endif
