/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/03/21 20:27:27 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include "errno.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

# define MAX_PHILOSOPHER 200

typedef enum e_philo_state
{
	HUNGRY,
	EATING,
	SLEEP,
	THINKING,
	DIED
}			t_philo_state;

typedef struct s_param
{
	int32_t		num_philo;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	int32_t		eat_at_least;
}					t_param;

typedef struct s_philo
{
	int32_t			name;
	t_param			*param;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	bool			**l_fork;
	bool			**r_fork;
	bool			is_authorized;
	uint64_t		estimate_wait_time;
	uint64_t		*base_time;
	pthread_t		thread_id;
	t_philo_state	state;
	uint64_t		last_meal;
	int64_t			limit;
	int32_t			eat_count;
	int32_t			position;
}					t_philo;


typedef struct s_counter
{
	int32_t		count;
	t_philo		*philo;
	pthread_t	thread_id;
}				t_counter;

typedef struct s_data
{
	pthread_mutex_t	*authorization;
	bool			auth_val;
	bool			*forks;
	t_philo			**philos;
	t_param			*param;
	pthread_t		**thread_ids;
}				t_data;

void				*free_all(void);
inline bool			*get_forks(void);
inline t_philo		**get_philosophers(void);
inline t_param		*get_params(void);
inline uint64_t		get_time_stamp();
inline int32_t		next_ph(const int32_t i, const int32_t philo_count);
inline int32_t		prev_ph(const int32_t i, const int32_t philo_count);
inline t_data		*get_data(void);
void				take_forks(t_philo *ph);

void			*init_forks(void);
void			init_params(int32_t argc, char **argv);
void			*init_philosophers(void);
void			*init_dispatchers(void);

#endif
