/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/28 18:19:40 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_to_buffer(const char *msg, t_philo *ph, t_print_buffer *buff)
{
	char	*write_buff;
	int32_t	i;

	if (buff->stop_print)
		return ;
	i = buff->count;
	write_buff = buff->write;
	i += uint32_to_str((uint32_t)ph->last_action / 1000, &write_buff[i]);
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
	if (write(STDOUT_FILENO, read_buff, count) == -1)
		return (true);
	return (stop_print);
}
