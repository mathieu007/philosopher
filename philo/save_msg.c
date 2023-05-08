/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 16:01:01 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	save_die_msg(t_philo *ph, t_data *data, int32_t msg_index)
{	
	if (!data->exit_threads && data->buffer->stop_count == 0)
	{
		ph->exit_status = 1;
		ph->last_action = get_time_stamp_mc();
		data->buffer->count += DIED_MSG_LEN + 10;
		save_to_buffer_at(" died\n", ph, data->buffer->write, msg_index);
		data->buffer->stop_count = data->buffer->count;
	}
}

inline int32_t	save_eat(t_philo *ph, t_data *data, int32_t time_to_die)
{	
	bool			exit;
	int32_t			msg_index;
	char			*write_buff;
	
	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += EAT_MSG_LEN + 10;
	exit = data->exit_threads;
	write_buff = data->buffer->write;
	ph->last_action = get_time_stamp_mc();
	if (exit)
	{
		ph->exit_status = 1;
		pthread_mutex_unlock(data->write);
		return (msg_index);
	}
	if (ph->last_action > ph->last_meal + time_to_die)
	{
		ph->exit_status = 1;
		data->buffer->count -= EAT_MSG_LEN + 10;
		save_die_msg(ph, data, msg_index);
		pthread_mutex_unlock(data->write);
		return (msg_index);
	}
	pthread_mutex_unlock(data->write);	
	save_to_buffer_at(" is eating\n", ph, write_buff, msg_index);
	ph->last_meal = ph->last_action;
	return (msg_index);
}

inline int32_t	save_msg(const char *msg, int32_t msg_len, t_philo *ph, t_data *data)
{	
	bool	exit;
	int32_t	msg_index;
	char	*write;

	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += msg_len + 10;
	exit = data->exit_threads;
	write = data->buffer->write;
	ph->last_action = get_time_stamp_mc();
	if (exit)
	{
		ph->exit_status = 1;
		pthread_mutex_unlock(data->write);
		return (msg_index);
	}
	pthread_mutex_unlock(data->write);
	save_to_buffer_at(msg, ph, write, msg_index);
	return (msg_index);
}
