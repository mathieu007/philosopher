/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:46:51 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_fifo	*fifo_add(t_fifo *fifo, t_philo *ph)
{
	pthread_mutex_lock(fifo->lock);
	fifo->head = head_prev(fifo);
	fifo->phs[fifo->head] = ph;
	fifo->count++;
	pthread_mutex_unlock(fifo->lock);
	return (fifo);
}

t_fifo	*fifo_add_pop(t_fifo *fifo, t_philo *ph)
{
	pthread_mutex_lock(fifo->lock);
	fifo->head = head_prev(fifo);
	fifo->phs[fifo->head] = ph;
	fifo->count++;
	if (fifo->count > 1)
		fifo->tail = tail_prev(fifo);
	pthread_mutex_unlock(fifo->lock);
	return (fifo);
}
