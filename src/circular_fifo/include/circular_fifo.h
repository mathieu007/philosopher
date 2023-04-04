/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_fifo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:21:35 by mroy              #+#    #+#             */
/*   Updated: 2023/04/03 20:50:22 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULAR_FIFO_H
# define CIRCULAR_FIFO_H

# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_fifo
{
	int32_t			_count;
	int32_t			_max_len;
	int32_t			_head;
	pthread_mutex_t	*_lock;
	int32_t			_tail;
	void			**_data;
}					t_fifo;

int32_t		next(t_fifo *fifo, const int32_t i);
int32_t		prev(t_fifo *fifo, const int32_t i);
t_fifo		*new_fifo(size_t elem_count);
void		*fifo_get(t_fifo *fifo);
void		*fifo_get_pop(t_fifo *fifo);
void		fifo_put(t_fifo *fifo, void *value);
void		fifo_pop(t_fifo *fifo);
void		*fifo_concurent_get_pop(t_fifo *fifo);
void		fifo_concurrent_put(t_fifo *fifo, void *value);
void		fifo_concurrent_pop(t_fifo *fifo);
void		*fifo_concurent_get(t_fifo *fifo);
// void		fifo_fair_put(t_fifo *fifo, void *value, int32_t offset);
// void		fifo_concurrent_put_update(t_fifo *fifo, void *value, void (*update)(void *));
int32_t		at_index(t_fifo *fifo, const int32_t i);
void		*fifo_concurent_get_at(t_fifo *fifo, int32_t i);
void		fifo_concurrent_put_exec(t_fifo *fifo, void *value, void (*func)(t_fifo *, void *));
void		*fifo_get_at(t_fifo *fifo, int32_t i);
void		fifo_concurrent_put_swap(t_fifo *fifo, void *value, bool (*should_swap)(void *, void *));
void		fifo_concurrent_swap_tail(t_fifo *fifo, void *value, bool (*should_swap)(void *, void *));

#endif
