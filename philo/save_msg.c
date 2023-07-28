/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/27 15:40:33 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_die_msg(t_philo *ph, t_data *data, int32_t msg_index)
{
	if (!data->exit_threads && data->buffer->stop_count == 0)
	{
		ph->exit_status = 1;
		ph->last_action = get_time_stamp_mc();
		data->buffer->count += DIED_MSG_LEN + 10;
		ph->msg = " died\n";
		save_to_buffer_at(ph->last_action, ph, data, msg_index);
		data->buffer->stop_count = data->buffer->count;
	}
}

int64_t	save_eat(t_philo *ph, t_data *data, int32_t time_to_die)
{
	int32_t	msg_index;
	int64_t	last_action;

	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += EAT_MSG_LEN + 10;
	ph->last_action = get_time_stamp_mc();
	last_action = ph->last_action;
	if (data->exit_threads)
	{
		ph->exit_status = 1;
		pthread_mutex_unlock(data->write);
		return (last_action);
	}
	if (last_action > ph->last_meal + time_to_die)
	{
		ph->exit_status = 1;
		data->buffer->count -= EAT_MSG_LEN + 10;
		save_die_msg(ph, data, msg_index);
		pthread_mutex_unlock(data->write);
		return (last_action);
	}
	ph->last_meal = last_action;
	ph->msg = " is eating\n";
	save_to_buffer_at(last_action, ph, data, msg_index);
	pthread_mutex_unlock(data->write);
	return (last_action);
}

int64_t	save_msg(char *msg, int32_t msg_len, t_philo *ph, t_data *data)
{
	int32_t	msg_index;
	int64_t	last_action;

	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += msg_len + 10;
	ph->last_action = get_time_stamp_mc();
	last_action = ph->last_action;
	if (data->exit_threads)
	{
		ph->exit_status = 1;
		pthread_mutex_unlock(data->write);
		return (last_action);
	}
	ph->msg = msg;
	save_to_buffer_at(last_action, ph, data, msg_index);
	pthread_mutex_unlock(data->write);
	return (last_action);
}
