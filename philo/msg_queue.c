/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/27 11:20:52 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_dead_msg(const char *msg, int32_t time, t_philo *ph,
	t_print_buffer *buff)
{
	save_msg(msg, time, ph, buff);
	buff->stop_print = true;
	buff->stop_count = buff->count;
}

void	save_msg(const char *msg, int32_t time, t_philo *ph,
	t_print_buffer *buff)
{
	char	*write_buff;
	int32_t	i;

	if (buff->stop_print)
		return ;
	i = buff->count;
	write_buff = buff->write;
	i += uint32_to_str((uint32_t)time, &write_buff[i]);
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
