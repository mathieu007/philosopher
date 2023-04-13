/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/04/13 07:00:00 by math             ###   ########.fr       */
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

typedef struct s_param
{
	int32_t		num_philo;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	int32_t		time_to_think;
	int32_t		time_cycle;
	int32_t		must_eat;
}					t_param;

typedef struct s_philo
{
	int32_t				name;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*process_mutex;
	bool				*process;
	pthread_t			thread_id;
	int32_t				last_meal;
	int32_t				exit_status;
	int32_t				last_think;
	int32_t				eat_count;
	int32_t				position;
	t_param				*params;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
	uint64_t		base_time;
	t_philo			**philos;
	pthread_t		*thread_ids;
	t_param			*params;
	bool			exit_threads;
}				t_data;


t_param			*get_params(void);
int32_t			get_relative_time_mc(const t_data *data);
int32_t			get_relative_time_ms(const t_data *data);
int32_t			next_ph(const int32_t i, const int32_t philo_count);
int32_t			prev_ph(const int32_t i, const int32_t philo_count);
t_data			*get_data(void);
void			take_forks(t_philo *ph);
uint64_t		get_time_stamp_ms(void);
uint64_t		get_time_stamp_mc(void);
int32_t			print_msg(const char *msg, t_philo *ph, t_data *data);
int32_t			print_die_msg(const char *msg, t_philo *ph, t_data *data);
bool			exit_threads(bool update_val);
bool			should_exit(void);
t_philo			**get_philosophers(void);
void			*philo_odd_work(void *philo);
void			*philo_even_work(void *philo);
void			process_odd_wait_list(t_philo **phs, int32_t ph_cnt);
void			process_even_wait_list(t_philo **phs, int32_t ph_cnt);
t_philo			**get_thread_philo(void);
void			*free_threads(void);
void			*free_mutexes(void);
void			*free_all(void);
void			*free_philo(t_philo	*ph);
pthread_mutexattr_t	*get_mutex_attr(void);
void			*join_threads(void);
bool			should_exit_ph(t_philo *ph);
bool			is_odd(int32_t num);
bool			is_even(int32_t num);

void	lock_all_philos(void);
bool	try_init_params(int32_t argc, char **argv);
void	*init_philosophers(void);
void	*init_dispatchers(void);
void	*init_threads(void);
void	init_mutexes(void);
void	start_simulation(int32_t ph_cnt);
void	*free_forks(void);
void	*free_exit_thread(void);
void	*free_exit_all_threads(void);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);

#endif
