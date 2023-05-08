/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/05/08 11:24:45 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# define SLEEP_BUFFER 2000
# define EAT_MSG_LEN 12
# define SLEEP_MSG_LEN 14
# define THINK_MSG_LEN 14
# define DIED_MSG_LEN 7
# define TAKE_A_FORK_MSG_LEN 19

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


typedef struct s_msg
{
	char		*msg;
	int32_t		ph_name;
	int32_t		time;
}				t_msg;

typedef struct s_print_buffer
{
	char				*read;
	char				*write;
	int32_t				count;
	pthread_t			thread_id;
	bool				stop_print;
	int32_t				stop_count;
}					t_print_buffer;

typedef struct s_param
{
	const int64_t	num_philo;
	const int64_t	time_to_die;
	const int64_t	time_to_eat;
	const int64_t	time_to_sleep;
	const int64_t	time_to_think;
	const int64_t	time_cycle;
	const int32_t	must_eat;
}					t_param;

typedef struct s_philo
{
	int32_t				name;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	bool				*left_fork_taken;
	bool				*right_fork_taken;
	pthread_mutex_t		*start_simulation;
	pthread_t			thread_id;
	const int64_t		base_time;
	int64_t				last_action;
	int64_t				last_meal;
	int32_t				exit_status;
	int64_t				last_think;
	const int64_t		start_time;
	int64_t				interval;
	int32_t				eat_count;
	int32_t				position;
	t_param				*params;
	struct s_data		*data;
}						t_philo;


typedef struct s_fifo
{
	t_philo				**phs;
	pthread_mutex_t		*lock;
	int32_t				count;
	int32_t				len;
	int32_t				head;
	int32_t				tail;
}						t_fifo;

typedef struct s_data
{
	pthread_mutex_t	*cycle;
	pthread_mutex_t	*write;
	pthread_mutex_t	*forks;
	bool			*forks_taken;
	t_fifo			*queue;
	t_philo			**dispatch_order;
	int32_t			last_philo_index_in_queue;
	const int64_t	base_time;
	int32_t			threads_ready;
	t_philo			**philos;
	pthread_t		*thread_ids;
	t_param			*params;
	bool			exit_threads;
	t_print_buffer	*buffer;
}				t_data;

t_fifo			*fifo_new(int32_t count);
t_fifo			*fifo_add_pop(t_fifo *fifo, t_philo *ph);
t_fifo			*fifo_add(t_fifo *fifo, t_philo *ph);
t_fifo			*fifo_pop(t_fifo *fifo);
t_philo			*fifo_get_pop(t_fifo *fifo);
t_philo			*fifo_get(t_fifo *fifo);
int32_t			tail_prev(t_fifo *fifo);
int32_t			head_prev(t_fifo *fifo);
int32_t			tail_next(t_fifo *fifo);
size_t			uint32_to_str(uint32_t value, char *dst);
int64_t			get_interval(void);
void			dispatch_philos(t_philo **phs, int32_t ph_cnt);
void			wait_threads_ready(t_data *data, int32_t ph_cnt);
t_param			*get_params(void);
int32_t			get_relative_time_mc(const t_philo *ph);
int32_t			get_relative_time_ms(const t_philo *ph);
int32_t			prev_ph(const int32_t i, int32_t philo_count);
t_data			*get_data(void);
void			take_forks(t_philo *ph);
void			put_forks_on_table(t_philo *ph);
int64_t			get_time_stamp_ms(void);
int64_t			get_time_stamp_mc(void);
int32_t			save_msg(const char *msg, int32_t msg_len, t_philo *ph, t_data *data);
void			save_die_msg(t_philo *ph, t_data *data, int32_t msg_index);
int32_t			save_eat(t_philo *ph, t_data *data, int32_t time_to_die);
void			three_stage_sleep(int64_t time_to_sleep, int64_t end_time);
int64_t			two_stage_sleep(int64_t time_to_sleep, int64_t end_time);
bool			exit_threads(bool update_val);
t_philo			**get_philosophers(void);
void			*philo_odd_work(void *philo);
void			*philo_even_work(void *philo);
void			process_odd_wait_list(t_philo **phs, int32_t ph_cnt);
void			process_even_wait_list(t_philo **phs, int32_t ph_cnt);
t_philo			**get_thread_philo(void);
void			*free_threads(void);
void			*free_mutexes(void);
void			*free_all(void);
void			*free_philo(t_philo	*ph, int32_t i);
void			*join_threads(void);
bool			should_exit_ph(t_philo *ph);
bool			is_odd(int32_t num);
bool			is_even(int32_t num);

void			set_constant_char(const char val, const char *addr);
void			set_constant(const int32_t val, const int32_t *addr);
void			set_constant64(const int64_t val, const int64_t *addr);
void			lock_all_philos(void);
bool			try_init_params(int32_t argc, char **argv);
void			*init_philosophers(void);
void			*init_dispatchers(void);
void			*init_threads(void);
void			*init_mutexes(void);
void			*start_simulation(void);
void			*free_forks(void);
void			*free_exit_thread(void);
void			*free_exit_all_threads(void);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			save_to_buffer(const char *msg, t_philo *ph, t_print_buffer *buff);
bool			print_msg_buffer(t_data *data);
void			*init_print_buffer(void);
void			save_to_buffer_at(const char *msg, t_philo *ph,
					char *write, int32_t msg_index);

void			eating(t_philo *ph, t_data *data, int64_t time_to_eat, int64_t time_to_die);
void			sleeping(t_philo *ph, t_data *data,
					const int64_t time_to_sleep);
void			thinking(t_philo *ph, t_data *data);
void			sleeper(int64_t end_time);

void			set_philo_timing(int64_t start_time, t_philo *ph,
					const t_data *data, const t_param *params);
void			set_philos_timing(int64_t start_time, int32_t ph_cnt, int32_t i,
					int32_t rev_i);
int32_t			set_event_index(int32_t ph_cnt);
int32_t			set_odd_index(int32_t ph_cnt);
void			set_philo_start_time(int32_t ph_cnt);

int32_t			hard_code_1philo(void);
int32_t			error_msg(const char *msg);
int32_t			handle_parse_n_error(int32_t argc, char **argv);

#endif
