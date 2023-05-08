/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/07 16:34:18 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	head_prev(t_fifo *fifo)
{
	return ((fifo->head - 1 + fifo->count) % fifo->count);
}

inline int32_t	tail_prev(t_fifo *fifo)
{
	return ((fifo->tail - 1 + fifo->count) % fifo->count);
}

inline int32_t	tail_next(t_fifo *fifo)
{
	return (fifo->tail + 1 % fifo->count);
}