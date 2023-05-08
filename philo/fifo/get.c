/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:42:11 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*fifo_get_pop(t_fifo *fifo)
{
	t_philo	*ph;

	ph = NULL;
	pthread_mutex_lock(fifo->lock);
	if (fifo->count > 0)
	{
		ph = fifo->phs[fifo->tail];
		fifo->tail = tail_prev(fifo);
		fifo->count--;
	}
	pthread_mutex_unlock(fifo->lock);
	return (ph);
}

t_philo	*fifo_get(t_fifo *fifo)
{
	t_philo	*ph;

	ph = NULL;
	pthread_mutex_lock(fifo->lock);
	if (fifo->count > 0)
		ph = fifo->phs[fifo->tail];
	pthread_mutex_unlock(fifo->lock);
	return (ph);
}
