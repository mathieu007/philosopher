/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/01 19:13:46 by math             ###   ########.fr       */
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
	pthread_mutex_lock(fifo->_tail_lock);
	fifo->_tail = prev(fifo, fifo->_tail);
	pthread_mutex_unlock(fifo->_tail_lock);
	pthread_mutex_lock(fifo->_count_lock);
	fifo->_count--;
	pthread_mutex_unlock(fifo->_count_lock);
}
