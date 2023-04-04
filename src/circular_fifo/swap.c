/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 20:53:54 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"
#include "philosopher.h"

// inline void	fifo_concurrent_swap_tail(t_fifo *fifo, void *value, bool (*should_swap)(void *, void *))
// {
// 	int32_t	prev_tail;
// 	void	*temp;

// 	pthread_mutex_lock(fifo->_lock);
// 	prev_tail = prev(fifo, fifo->_tail);
// 	if (fifo->_count > 1 && value == fifo->items[fifo->_tail] && should_swap(value, fifo->items[prev_tail]))
// 	{
// 		temp = fifo->items[fifo->_tail];
// 		fifo->items[fifo->_tail] = fifo->items[prev_tail];
// 		fifo->items[prev_tail] = temp;
// 		printf("swap tail\n");
// 	}
// 	pthread_mutex_unlock(fifo->_lock);
// }

// inline void	fifo_concurrent_put_swap(t_fifo *fifo, void *value, bool (*should_swap)(void *, void *))
// {
// 	int32_t	new_head;

// 	pthread_mutex_lock(fifo->_lock);
// 	new_head = prev(fifo, fifo->_head);
// 	if (fifo->_count > 1 && should_swap(fifo->items[fifo->_head], value))
// 	{
// 		fifo->items[new_head] = fifo->items[fifo->_head];
// 		fifo->items[fifo->_head] = value;
// 		printf("swap\n");
// 	}
// 	else
// 		fifo->items[new_head] = value;
// 	fifo->_head = new_head;
// 	fifo->_count++;
// 	pthread_mutex_unlock(fifo->_lock);
// }
