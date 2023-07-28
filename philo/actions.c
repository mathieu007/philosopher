/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/28 12:29:02 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline bool	die_in_action(t_philo *ph, t_data *data, int32_t action_time)
{
	if (ph->exit_status == 0 && ph->death_time < ph->last_action + action_time)
	{
		three_stage_sleep(ph, ph->death_time - ph->last_action, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	return (false);
}

inline void	three_stage_sleep(const t_philo *ph, int32_t time_to_sleep,
	int32_t end_time)
{
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
	}
	if (time > 0)
		usleep(time);
}

static inline void	think_sleeper(const t_philo *ph, int32_t end_time)
{
	int32_t	time;

	time = (end_time - get_relative_time_mc(ph)) / 2;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph) - 500;
		if (time > 0)
			usleep(time);
	}
	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
}

inline int32_t	two_stage_sleep(const t_philo *ph, int32_t time_to_sleep, 
	int32_t end_time)
{
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
	}
	return (time);
}

inline void	eating(t_philo *ph, t_data *data)
{
	int32_t	time;

	save_eat(ph, data);
	if (die_in_action(ph, data, ph->time_to_eat))
		return ;
	time = two_stage_sleep(ph, ph->time_to_eat,
			ph->last_meal + ph->time_to_eat);
	if (time > 0)
		usleep(time);
	pthread_mutex_lock(data->write);
	*(ph->left_fork_taken) = false;
	*(ph->right_fork_taken) = false;
	pthread_mutex_unlock(data->write);
}

inline void	sleeping(t_philo *ph, t_data *data)
{
	save_msg(" is sleeping\n", ph, data);
	if (die_in_action(ph, data, ph->time_to_sleep))
		return ;
	three_stage_sleep(ph, ph->time_to_sleep,
		ph->last_action + ph->time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data)
{
	const int32_t	time_cycle = ph->params->time_cycle;

	save_msg(" is thinking\n", ph, data);
	if (die_in_action(ph, data, 0))
		return ;
	ph->last_think += (int64_t)time_cycle;
	think_sleeper(ph, (int32_t)(ph->last_think - ph->base_time));
}
