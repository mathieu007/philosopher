/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 14:43:13 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

inline void	*fifo_get(t_fifo *fifo)
{
	if (fifo->_count <= 0)
		return (NULL);
	return (fifo->items[fifo->_tail]);
}

inline void	*fifo_get_at(t_fifo *fifo, int32_t i)
{
	if (fifo->_count <= 0)
		return (NULL);
	return (fifo->items[at_index(fifo, i)]);
}

inline void	*fifo_get_pop(t_fifo *fifo)
{
	int32_t	index;

	if (fifo->_count <= 0)
		return (NULL);
	index = fifo->_tail;
	fifo->_tail = prev(fifo, index);
	return (fifo->items[index]);
}

inline void	*fifo_concurent_get_pop(t_fifo *fifo)
{
	int32_t	index;
	void	*val;

	if (fifo->_count <= 0)
		return (NULL);
	pthread_mutex_lock(fifo->_lock);
	index = fifo->_tail;
	fifo->_tail = prev(fifo, index);
	val = fifo->items[index];
	pthread_mutex_unlock(fifo->_lock);
	return (val);
}

inline void	*fifo_concurent_get(t_fifo *fifo)
{
	void	*val;

	if (fifo->_count <= 0)
		return (NULL);
	pthread_mutex_lock(fifo->_lock);
	val = fifo->items[fifo->_tail];
	pthread_mutex_unlock(fifo->_lock);
	return (val);
}

inline void	*fifo_concurent_get_at(t_fifo *fifo, int32_t i)
{
	void	*val;

	if (fifo->_count <= 0 || fifo->_count <= i)
		return (NULL);
	pthread_mutex_lock(fifo->_lock);
	val = fifo->items[at_index(fifo, i)];
	pthread_mutex_unlock(fifo->_lock);
	return (val);
}
