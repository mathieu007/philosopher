/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/27 19:22:24 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// static bool	is_dead(t_philo *ph, t_data *data)
// {
// 	bool			left_fork;
// 	bool			right_fork;
// 	int32_t			interval;
// 	int64_t			max_time;
// 	int64_t			curr_time;

// 	curr_time = get_time_stamp_mc();
// 	max_time = ph->last_think + ((data->params->time_to_think * 1000) / 2);
// 	interval = (max_time - curr_time) / 5;
// 	while (curr_time < max_time)
// 	{
// 		pthread_mutex_lock(data->write);
// 		left_fork = *(ph->left_fork_taken);
// 		right_fork = *(ph->right_fork_taken);
// 		pthread_mutex_unlock(data->write);
// 		if (left_fork || right_fork)
// 			usleep(interval);
// 		else
// 			return (false);
// 		curr_time += interval;
// 	}
// 	return (true);
// }

static inline void	inner_philo_even(t_philo *ph, t_data *data,
	const int64_t time_to_eat, const int64_t time_to_sleep)
{	
	const int64_t time_to_die = (data->params->time_to_die);

	fifo_add_pop(data->queue, ph);
	pthread_mutex_lock(ph->left_fork);
	save_msg(" has taken a fork\n", TAKE_A_FORK_MSG_LEN, ph, data);
	pthread_mutex_lock(ph->right_fork);
	save_msg(" has taken a fork\n", TAKE_A_FORK_MSG_LEN, ph, data);
	eating(ph, data, time_to_eat, time_to_die);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
}

void	*philo_even_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int64_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat;
	const int64_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	ph->last_action = ph->last_think;
	ph->last_meal = ph->start_time;
	while (true)
	{
		if (ph->start_time <= get_time_stamp_mc() + 25)
			break ;
		usleep(100);
	}
	while (eat_count > 0 && ph->exit_status != 1)
	{	
		inner_philo_even(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}

static inline void	inner_philo_odd(t_philo *ph, t_data *data,
	int64_t time_to_eat, int64_t time_to_sleep)
{
	const int64_t	time_to_die = (data->params->time_to_die);

	fifo_add_pop(data->queue, ph);
	pthread_mutex_lock(ph->right_fork);
	save_msg(" has taken a fork\n", TAKE_A_FORK_MSG_LEN, ph, data);
	pthread_mutex_lock(ph->left_fork);
	save_msg(" has taken a fork\n", TAKE_A_FORK_MSG_LEN, ph, data);
	eating(ph, data, time_to_eat, time_to_die);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
}

void	*philo_odd_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int64_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat;
	const int64_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	ph->last_action = ph->last_think;
	ph->last_meal = ph->start_time;
	while (true)
	{
		if (ph->start_time <= get_time_stamp_mc() + 25)
			break ;
		usleep(50);
	}
	while (eat_count && ph->exit_status != 1)
	{
		inner_philo_odd(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}
