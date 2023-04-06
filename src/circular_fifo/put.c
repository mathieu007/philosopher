/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 09:53:56 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

inline void	fifo_put(t_fifo *fifo, void *value)
{	
	fifo->_head = prev(fifo, fifo->_head);
	fifo->_data[fifo->_head] = value;
	fifo->_count++;
}

inline void	fifo_concurrent_put(t_fifo *fifo, void *value)
{	
	int32_t	head;

	pthread_mutex_lock(fifo->_lock);
	head = prev(fifo, fifo->_head);
	fifo->_head = head;
	fifo->_data[head] = value;
	fifo->_count++;
	pthread_mutex_unlock(fifo->_lock);
}

/// @brief On linux and windows mutex are not implemented as "fair" mutex,
/// mutex are not guaranteed to be dispatched in the order they enter.
/// they are much faster on linux and windows, but are not ordered.
/// this function put the data in ordered manner.
/// @param fifo 
/// @param value 
/// @param offset 
// inline void	fifo_fair_put(t_fifo *fifo, void *value, int32_t offset)
// {
// 	int32_t	old_time;
// 	int32_t	new_time;
// 	int32_t	i;
// 	void	*old_value;

// 	pthread_mutex_lock(fifo->_lock);
// 	new_time = *((int32_t *)&((uint8_t *)value)[offset]);
// 	i = fifo->_head;
// 	old_value = fifo->_data[i];
// 	old_time = *((int32_t *)&((uint8_t *)old_value)[offset]);
// 	if (old_time > new_time)
// 	{
// 		while (i <= fifo->_tail)
// 		{
// 			old_value = fifo->_data[i];
// 			old_time = *((int32_t *)&((uint8_t *)old_value)[offset]);
// 			if (old_time > new_time)
// 				fifo->_data[prev(fifo, i)] = old_value;
// 			else
// 			{
// 				i = next(fifo, i);
// 				break ;
// 			}
// 			i = next(fifo, i);
// 		}
// 		fifo->_head = prev(fifo, fifo->_head);
// 		fifo->_data[prev(fifo, i - 1)] = value;
// 		fifo->_count++;
// 		pthread_mutex_unlock(fifo->_lock);
// 		return ;
// 	}
// 	fifo->_head = prev(fifo, fifo->_head);
// 	fifo->_data[fifo->_head] = value;
// 	fifo->_count++;
// 	pthread_mutex_unlock(fifo->_lock);
// }
