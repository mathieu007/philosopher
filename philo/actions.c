/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/06 13:45:40 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	three_stage_sleep(int64_t time_to_sleep, int64_t end_time)
{	
	int64_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	time = end_time - get_time_stamp_mc();
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	if (time > 0)
		usleep(time);
}

static inline void	think_sleeper(int64_t end_time)
{	
	int64_t	time;

	time = (end_time - get_time_stamp_mc());
	if (time > 0)
	{
		usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	if (time > 0)
		usleep(time);
}

inline int64_t	two_stage_sleep(int64_t time_to_sleep, int64_t end_time)
{
	int64_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
	{
		usleep(time);
		time = end_time - get_time_stamp_mc();
	}
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	return (time);
}

inline void	eating(t_philo *ph, t_data *data, const int64_t time_to_eat, const int64_t time_to_die)
{
	int64_t	time;
	int64_t	death_time;

	save_eat(ph, data, time_to_die);
	death_time = ph->last_meal + time_to_die;
	if (ph->last_action + time_to_eat > death_time)
	{
		usleep((ph->last_action + time_to_eat) - death_time);
		save_die_msg(ph, data);
	}
	time = two_stage_sleep(time_to_eat, (ph->last_meal + time_to_eat));
	pthread_mutex_lock(data->write);
	*(ph->left_fork_taken) = false;
	*(ph->right_fork_taken) = false;
	pthread_mutex_unlock(data->write);
	if (time > 0)
		usleep(time);
}

inline void	sleeping(t_philo *ph, t_data *data, const int64_t time_to_sleep, const int64_t death_time)
{
	save_msg(" is sleeping\n", ph, data);
	if (ph->last_action + time_to_sleep > death_time)
	{
		usleep((ph->last_action + time_to_sleep) - death_time);
		save_die_msg(ph, data);
	}
	three_stage_sleep(time_to_sleep, ph->last_action + time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data, const int64_t death_time)
{
	const int64_t	time_cycle = ph->params->time_cycle;

	save_msg(" is thinking\n", ph, data);
	if (ph->last_action > death_time)
	{
		usleep(ph->last_action - death_time);
		save_die_msg(ph, data);
	}
	ph->last_think += time_cycle;
	think_sleeper(ph->last_think - ph->base_time);
}
