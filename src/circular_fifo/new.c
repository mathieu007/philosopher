/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 14:44:07 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"
t_fifo	*new_fifo(size_t elem_count, size_t elem_size)
{
	t_fifo				*fifo;
	// pthread_mutexattr_t	attr;

	// pthread_mutexattr_init(&attr);
	// pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_TIMED_NP);
	fifo = malloc(sizeof(t_fifo));
	fifo->_lock = malloc(sizeof(pthread_mutex_t));
	if (!fifo)
		return (NULL);
	fifo->items = malloc(elem_count * sizeof(t_item *));
	if (!(fifo->items))
		return (free(fifo), NULL);
	fifo->_count = 0;
	fifo->_max_len = elem_count;
	fifo->_tail = elem_count - 1;
	fifo->_head = elem_count;
	pthread_mutex_init(fifo->_lock, NULL);
	return (fifo);
}