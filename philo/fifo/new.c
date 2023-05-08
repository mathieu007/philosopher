/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 10:27:15 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_fifo	*fifo_new(int32_t count)
{
	t_fifo	*fifo;

	fifo = malloc(sizeof(t_fifo));
	fifo->head = 1;
	fifo->tail = 0;
	fifo->count = 0;
	fifo->len = count;
	fifo->lock = malloc(sizeof(pthread_mutex_t));
	fifo->phs = malloc(sizeof(t_philo *) * count);
	return (fifo);
}
