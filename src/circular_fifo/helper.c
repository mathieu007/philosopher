/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 20:52:58 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "circular_fifo.h"

inline int32_t	next(t_fifo *fifo, const int32_t i)
{
	return ((i + 1) % fifo->_max_len);
}

inline int32_t	at_(t_fifo *fifo, const int32_t i)
{
	return ((i + 1) % fifo->_max_len);
}

inline int32_t	prev(t_fifo *fifo, const int32_t i)
{
	return (((i - 1) + fifo->_max_len) % fifo->_max_len);
}

inline int32_t	at_index(t_fifo *fifo, const int32_t i)
{
	return (((fifo->_tail - i) + fifo->_max_len) % fifo->_max_len);
}

inline void	*get(t_fifo *fifo)
{
	return (fifo->_data[fifo->_tail]);
}