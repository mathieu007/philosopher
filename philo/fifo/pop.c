/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:43:32 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_fifo	*fifo_pop(t_fifo *fifo)
{
	pthread_mutex_lock(fifo->lock);
	if (fifo->count > 0)
	{
		fifo->tail = tail_prev(fifo);
		fifo->count--;
	}
	pthread_mutex_unlock(fifo->lock);
	return (fifo);
}
