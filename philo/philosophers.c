/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/26 16:11:37 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static bool	is_dead(t_philo *ph, t_data *data)
{
	bool			left_fork;
	bool			right_fork;
	int32_t			interval;
	int64_t			max_time;
	int64_t			curr_time;

	curr_time = get_time_stamp_mc();
	max_time = ph->last_think + ((data->params->time_to_think * 1000) / 2);
	interval = (max_time - curr_time) / 5;
	while (curr_time < max_time)
	{
		pthread_mutex_lock(data->write);
		left_fork = *(ph->left_fork_taken);
		right_fork = *(ph->right_fork_taken);
		pthread_mutex_unlock(data->write);
		if (left_fork || right_fork)
			usleep(interval);
		else
			return (false);
		curr_time += interval;
	}
	return (true);
}

static inline void	inner_philo_even(t_philo *ph, t_data *data,
	const int32_t time_to_eat, const int32_t time_to_sleep)
{		
	pthread_mutex_lock(ph->left_fork);
	print_msg(" has taken a fork\n", ph, data);
	pthread_mutex_lock(ph->right_fork);
	print_msg(" has taken a fork\n", ph, data);
	eating(ph, data, time_to_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
	if (is_dead(ph, data))
		print_die_msg(ph, data);
}

void	*philo_even_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int32_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat * 1000;
	const int32_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep * 1000;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	while (eat_count > 0 && ph->exit_status != 1)
	{	
		inner_philo_even(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}

static inline void	inner_philo_odd(t_philo *ph, t_data *data,
	int32_t time_to_eat, int32_t time_to_sleep)
{
	pthread_mutex_lock(ph->right_fork);
	print_msg(" has taken a fork\n", ph, data);
	pthread_mutex_lock(ph->left_fork);
	print_msg(" has taken a fork\n", ph, data);
	eating(ph, data, time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
	if (is_dead(ph, data))
		print_die_msg(ph, data);
}

void	*philo_odd_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int32_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat * 1000;
	const int32_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep * 1000;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	while (eat_count && ph->exit_status != 1)
	{
		inner_philo_odd(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}
