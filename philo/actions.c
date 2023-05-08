/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 12:50:09 by mroy             ###   ########.fr       */
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

inline void	eating(t_philo *ph, t_data *data, int64_t time_to_eat, int64_t time_to_die)
{
	int64_t	time;
	int32_t	msg_index;

	msg_index = save_eat(ph, data, time_to_die);
	// death_time = ph->last_meal + time_to_die;
	// if (ph->last_action + time_to_eat > death_time)
	// {
	// 	usleep((ph->last_action + time_to_eat) - death_time);
	// 	pthread_mutex_lock(data->write);
	// 	save_die_msg(ph, data, msg_index);
	// 	pthread_mutex_unlock(data->write);
	// }
	time = two_stage_sleep(time_to_eat, (ph->last_meal + time_to_eat));
	if (time > 0)
		usleep(time);
}

inline void	sleeping(t_philo *ph, t_data *data, int64_t time_to_sleep)
{
	int32_t	msg_index;

	msg_index = save_msg(" is sleeping\n", SLEEP_MSG_LEN, ph, data);
	// if (ph->last_action + time_to_sleep > death_time)
	// {
	// 	usleep((ph->last_action + time_to_sleep) - death_time);
	// 	pthread_mutex_lock(data->write);
	// 	save_die_msg(ph, data, msg_index);
	// 	pthread_mutex_unlock(data->write);
	// }
	three_stage_sleep(time_to_sleep, ph->last_action + time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data)
{
	const int64_t	time_cycle = ph->params->time_cycle;
	int32_t			msg_index;

	msg_index = save_msg(" is thinking\n", THINK_MSG_LEN, ph, data);
	// if (ph->last_action > death_time)
	// {
	// 	usleep(ph->last_action - death_time);
	// 	pthread_mutex_lock(data->write);
	// 	save_die_msg(ph, data, msg_index);
	// 	pthread_mutex_unlock(data->write);
	// }
	ph->last_think += time_cycle;
	think_sleeper(ph->last_think - ph->base_time);
}
