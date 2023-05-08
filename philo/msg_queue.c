/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 16:01:53 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_to_buffer_at(const char *msg, t_philo *ph, char *write_buff, int32_t msg_index)
{
	int32_t			len;
	// t_print_buffer	*buff;

	// buff = ph->data->buffer;
	// if (ph->data->buffer->stop_count != 0)
	// 	return ;
	len = uint32_to_str((uint32_t)(ph->last_action - ph->base_time) / 1000, &write_buff[msg_index]);
	msg_index += len;
	while (len < 7)
	{
		write_buff[msg_index++] = ' ';
		len++;
	}
	len = uint32_to_str((uint32_t)ph->name, &write_buff[msg_index]);
	msg_index += len;
	while (len < 4)
	{
		write_buff[msg_index++] = ' ';
		len++;
	}
	while (*msg != '\0')
	{
		write_buff[msg_index] = *msg;
		msg++;
		msg_index++;
	}
}

void	save_to_buffer(const char *msg, t_philo *ph, t_print_buffer *buff)
{
	char	*write_buff;
	int32_t	i;

	if (buff->stop_print)
		return ;
	i = buff->count;
	write_buff = buff->write;
	i += uint32_to_str((uint32_t)(ph->last_action - ph->base_time) / 1000, &write_buff[i]);
	write_buff[i++] = ' ';
	i += uint32_to_str((uint32_t)ph->name, &write_buff[i]);
	while (*msg != '\0')
	{
		write_buff[i] = *msg;
		msg++;
		i++;
	}
	buff->count = i;
}

bool	print_msg_buffer(t_data *data)
{	
	char			*write_buff;
	char			*read_buff;
	int32_t			count;
	t_print_buffer	*buff;
	t_philo			*ph;

	ph = fifo_get(data->queue);
	pthread_mutex_lock(data->write);
	buff = data->buffer;
	count = buff->count;
	if (count == 0)
	{
		pthread_mutex_unlock(data->write);
		return (data->exit_threads);
	}
	if (buff->stop_count == 0 && get_time_stamp_mc() > ph->last_meal + data->params->time_to_die)
	{
		save_die_msg(ph, ph->data, buff->count);
	}		
	write_buff = buff->read;
	read_buff = buff->write;
	buff->write = write_buff;
	buff->read = read_buff;
	if (buff->stop_count != 0)
	{
		data->exit_threads = true;
		count = buff->stop_count;
	}
	buff->count = 0;
	pthread_mutex_unlock(data->write);
	write(STDOUT_FILENO, read_buff, count);
	return (data->exit_threads);
}
