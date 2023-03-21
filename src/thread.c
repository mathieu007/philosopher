/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 13:14:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline pthread_t	*get_thread(void)
{
	static pthread_t	dispatchers[MAX_PHILOSOPHER];

	return (&dispatchers[0]);
}

void	init_dispatchers(void)
{
	pthread_t	*threads;

	threads = get_thread();
	memset(threads, 0, MAX_PHILOSOPHER);
}

