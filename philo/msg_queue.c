/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/20 11:29:21 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	next(t_print_buffer *buff, const int32_t i)
{
	return ((i + 1) % buff->capacity);
}

void	save_msg(const char *msg, int32_t time, int32_t ph_name,
	t_print_buffer *buff)
{
	char	*write_buff;
	int32_t	i;

	i = buff->count;
	write_buff = buff->write;
	i += uint32_to_str((uint32_t)time, &write_buff[i]);
	write_buff[i++] = ' ';
	i += uint32_to_str((uint32_t)ph_name, &write_buff[i]);
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
	bool			exit;
	t_print_buffer	*buff;

	exit = false;
	pthread_mutex_lock(data->write);
	buff = data->buffer;
	write_buff = buff->read;
	read_buff = buff->write;
	buff->write = write_buff;
	buff->read = read_buff;
	exit = buff->exit;
	count = buff->count;
	buff->count = 0;
	pthread_mutex_unlock(data->write);
	read_buff[count] = '\0';
	write(STDOUT_FILENO, read_buff, count);
	// printf("%s", (const char *)read_buff);
	return (exit);
}
