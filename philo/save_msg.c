/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 07:27:43 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	save_die_msg(t_philo *ph, t_data *data, int32_t msg_index)
{	
	if (!data->exit_threads && !data->buffer->stop_print)
	{
		ph->exit_status = 1;
		ph->last_action = get_time_stamp_mc();
		save_to_buffer_at(" died\n", ph, data->buffer->write, msg_index);
		data->buffer->count -= DIED_MSG_LEN ;
		data->buffer->stop_print = true;
		data->buffer->stop_count = data->buffer->count;
	}
}

inline int32_t	save_eat(t_philo *ph, t_data *data)
{	
	bool			exit;
	int32_t			msg_index;
	char			*write_buff;
	bool			stop_print;

	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += EAT_MSG_LEN + 16;
	exit = data->exit_threads;
	write_buff = data->buffer->write;
	ph->last_action = get_time_stamp_mc();
	if (exit)
	{
		ph->exit_status = 1;
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
	bool	stop_print;

	pthread_mutex_lock(data->write);
	msg_index = data->buffer->count;
	data->buffer->count += msg_len + 16;
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
