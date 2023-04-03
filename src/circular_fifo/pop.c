/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 14:39:11 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

inline void	fifo_pop(t_fifo *fifo)
{
	fifo->_tail = prev(fifo, fifo->_tail);
	fifo->_count--;
}

inline void	fifo_concurrent_pop(t_fifo *fifo)
{
	pthread_mutex_lock(fifo->_lock);
	fifo->_tail = prev(fifo, fifo->_tail);
	fifo->_count--;
	pthread_mutex_unlock(fifo->_lock);
}
