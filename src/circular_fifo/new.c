/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/01 18:53:51 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

t_fifo	*new_fifo(size_t elem_count, size_t elem_size)
{
	t_fifo				*fifo;
	pthread_mutexattr_t	attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP);
	fifo = malloc(sizeof(t_fifo));
	fifo->_head_lock = malloc(sizeof(pthread_mutex_t));
	fifo->_tail_lock = malloc(sizeof(pthread_mutex_t));
	fifo->_count_lock = malloc(sizeof(pthread_mutex_t));
	if (!fifo)
		return (NULL);
	fifo->_data = malloc(elem_count * elem_size);
	if (!(fifo->_data))
		return (free(fifo), NULL);
	fifo->_count = 0;
	fifo->_max_len = elem_count;
	fifo->_tail = elem_count - 1;
	fifo->_head = elem_count;
	pthread_mutex_init(fifo->_head_lock, PTHREAD_MUTEX_TIMED_NP);
	pthread_mutex_init(fifo->_tail_lock, PTHREAD_MUTEX_TIMED_NP);
	pthread_mutex_init(fifo->_count_lock, PTHREAD_MUTEX_TIMED_NP);
	return (fifo);
}
