/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/07 09:03:25 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	save_to_buffer(const char *msg, t_philo *ph, t_print_buffer *buff)
{
	char	*write_buff;
	int32_t	i;

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

int32_t	count_buffer(t_print_buffer *buff, t_data *data)
{
	int32_t	count;
	bool	stop_print;

	stop_print = buff->stop_print;
	if (!stop_print)
		count = buff->count;
	else
	{
		data->exit_threads = true;
		count = buff->stop_count;
		buff->stop_count = 0;
	}
	buff->count = 0;
	return (count);
}

bool	print_msg_buffer(t_data *data)
{
	char			*write_buff;
	char			*read_buff;
	bool			stop_print;
	int32_t			count;
	t_print_buffer	*buff;

	pthread_mutex_lock(data->write);
	buff = data->buffer;
	write_buff = buff->read;
	read_buff = buff->write;
	buff->write = write_buff;
	buff->read = read_buff;
	count = count_buffer(buff, data);
	stop_print = buff->stop_print;
	pthread_mutex_unlock(data->write);
	if (stop_print)
	{
		write_buff = ft_strfind(read_buff, "died\n");
		if (write_buff != read_buff)
			count = write_buff - read_buff + 5;
	}
	if (write(STDOUT_FILENO, read_buff, count) == -1)
		return (true);
	return (stop_print);
}
