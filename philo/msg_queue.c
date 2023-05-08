/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:53:15 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_to_buffer_at(const char *msg, t_philo *ph, char *write_buff, int32_t msg_index)
{
	int32_t			len;
	// t_print_buffer	*buff;

	// buff = ph->data->buffer;
	// if (buff->stop_print)
	// 	return ;
	len = uint32_to_str((uint32_t)(ph->last_action - ph->base_time) / 1000, &write_buff[msg_index]);
	msg_index += len;
	while (len < 11)
	{
		write_buff[msg_index++] = ' ';
		len++;
	}
	len = uint32_to_str((uint32_t)ph->name, &write_buff[msg_index]);
	msg_index += len;
	while (len < 6)
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
	bool			stop_print;
	t_print_buffer	*buff;
	t_philo			*ph;

	ph = fifo_get(data->queue);
	stop_print = false;
	pthread_mutex_lock(data->write);
	buff = data->buffer;
	write_buff = buff->read;
	read_buff = buff->write;
	buff->write = write_buff;
	buff->read = read_buff;
	stop_print = buff->stop_print;
	if (!stop_print)
		count = buff->count;
	else
	{
		data->exit_threads = true;
		count = buff->stop_count;
	}
	buff->count = 0;
	pthread_mutex_unlock(data->write);
	write(STDOUT_FILENO, read_buff, count);
	return (stop_print);
}
