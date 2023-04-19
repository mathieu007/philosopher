/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/18 21:14:35 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	next(t_print_buffer *buff, const int32_t i)
{
	return ((i + 1) % buff->len);
}

inline int32_t	prev(t_print_buffer *buff, const int32_t i)
{
	return (((i - 1) + buff->len) % buff->len);
}

void	save_msg(const char *msg, int32_t time, int32_t ph_name, t_print_buffer *buff)
{	
	t_msg	*item;
	int32_t	tail;

	tail = next(buff, buff->tail);
	item = &(buff->msgs[tail]);
	item->msg = (char *)msg;
	item->time = time;
	item->ph_name = ph_name;
	buff->tail = tail;
}

inline bool	inner_print_msg_buffer(t_data *data, t_print_buffer *buff, int32_t head)
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
	pthread_mutex_unlock(data->write);
	printf(msg, time, name);
	return (exit);
}

bool	print_msg_buffer(t_data *data, t_print_buffer *buff)
{	
	int32_t		head;
	int32_t		tail;
	bool		exit;

	pthread_mutex_lock(data->write);
	tail = buff->tail;
	pthread_mutex_unlock(data->write);
	head = buff->head;
	if (head != -1)
	{
		while (head != tail)
		{
			inner_print_msg_buffer(data, buff, head);
			head = next(buff, head);
		}
		exit = inner_print_msg_buffer(data, buff, head);
		buff->head = head;
		if (exit)
			return (true);
	}
	return (false);
}
