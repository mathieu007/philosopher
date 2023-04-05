/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fifo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 17:18:40 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

void	*free_fifo(t_fifo *fifo)
{
	fifo = malloc(sizeof(t_fifo));
	pthread_mutex_destroy(fifo->_lock);
	free(fifo->_lock);
	free(fifo->_data);
	return (NULL);
}

