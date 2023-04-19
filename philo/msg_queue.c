/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/19 15:13:19 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	next(t_print_buffer *buff, const int32_t i)
{
	return ((i + 1) % buff->len);
}

// int32_t	prev(t_print_buffer *buff, const int32_t i)
// {
// 	return (((i - 1) + buff->len) % buff->len);
// }

void	save_msg(const char *msg, int32_t time, int32_t ph_name,
	t_print_buffer *buff)
{
	t_msg	*item;
	int32_t	tail;

	tail = next(buff, buff->tail);
	item = &(buff->msgs[tail]);
	item->msg = (char *)msg;
	item->time = time;
	item->ph_name = ph_name;
	buff->tail = tail;
	buff->count++;
}

bool	inner_print_msg_buffer(t_data *data, t_print_buffer *buff, int32_t head)
{
	t_msg		*mess;
	int32_t		name;
	int32_t		time;
	char		*msg;
	bool		exit;

	pthread_mutex_lock(data->write);
	mess = (&(buff->msgs[head]));
	name = mess->ph_name;
	msg = mess->msg;
	time = mess->time;
	exit = buff->exit;
	buff->count--;
	pthread_mutex_unlock(data->write);
	printf(msg, time, name);
	return (exit);
}

bool	inner_print_buffer(int32_t count, t_data *data, t_print_buffer *buff,
	int32_t head)
{
	bool	exit;

	exit = false;
	if (count == 0)
	{
		if (exit)
			return (true);
		else
			return (false);
	}
	while (true)
	{
		exit = inner_print_msg_buffer(data, buff, head);
		head = next(buff, head);
		count--;
		if (count == 0)
		{
			buff->head = head;
			break ;
		}	
	}
	return (exit);
}

bool	print_msg_buffer(t_data *data)
{	
	int32_t			tail;
	int32_t			count;
	bool			exit;
	t_print_buffer	*buff;

	exit = false;
	pthread_mutex_lock(data->write);
	buff = data->buffer;
	tail = buff->tail;
	count = buff->count;
	exit = buff->exit;
	pthread_mutex_unlock(data->write);
	exit = inner_print_buffer(count, data, buff, buff->head);
	if (exit)
	{		
		pthread_mutex_lock(data->write);
		count = buff->count;
		pthread_mutex_unlock(data->write);
		if (count != 0)
			print_msg_buffer(data);
		return (true);
	}
	return (false);
}
