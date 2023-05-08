/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:31:37 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_fifo	*fifo_new(int32_t count)
{
	t_fifo	*fifo;

	fifo = malloc(sizeof(t_fifo));
	fifo->head = 1;
	fifo->tail = 0;
	fifo->lock = malloc(sizeof(pthread_mutex_t));
	fifo->phs = malloc(sizeof(t_philo *) * count);
	return (fifo);
}
