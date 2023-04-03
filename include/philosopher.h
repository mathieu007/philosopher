/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/04/01 18:03:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <stdatomic.h>
# include "circular_fifo.h"


typedef struct s_param
{
	int32_t		num_philo;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	int32_t		time_to_think;
	int32_t		must_eat;
}					t_param;

typedef struct s_philo
{
	int32_t				name;
	pthread_mutex_t		*forks_auth;
	pthread_mutex_t		*forks_take;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	bool				is_eating;
	bool				forks_taken;
	bool				in_queue;
	pthread_t			thread_id;
	int32_t				last_meal;
	int32_t				eat_count;
	int32_t				position;
	t_param				*params;
	void				(*update_state)(void *, bool);
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	pthread_mutex_t	*meal_authorization;
	pthread_mutex_t	*write;
	t_philo			**philos;
	pthread_t		*thread_ids;
	t_fifo			*wait_queue;
	t_fifo			*urgent_queue;
	t_param			*params;
	bool			exit_threads;
}				t_data;


t_param			*get_params(void);
int32_t			get_relative_time_mc(void);
int32_t			get_relative_time_ms(void);
int32_t			next_ph(const int32_t i, const int32_t philo_count);
int32_t			prev_ph(const int32_t i, const int32_t philo_count);
t_data			*get_data(void);
void			take_forks(t_philo *ph);
void			put_forks_on_table(t_philo *ph);
uint64_t		get_time_stamp_ms(void);
uint64_t		get_time_stamp_mc(void);
uint64_t		get_base_time(void);
void			print_msg(const char *msg, t_philo *ph);
void			print_msg_time(const char *msg, t_philo *ph, int32_t time);
void			*philo_work(void *philo);
bool			should_exit(void);
t_philo			**get_philosophers(void);

pthread_mutexattr_t	get_mutex_attr(int32_t type);

void	lock_all_philos(void);
bool	try_init_params(int32_t argc, char **argv);
void	*init_philosophers(void);
void	*init_dispatchers(void);
void	*init_threads(void);
void	init_mutexes(void);
void	start_work_load(void);
void	*free_forks(void);
void	*free_exit_thread(void);
void	*free_exit_all_threads(void);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif
