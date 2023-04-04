/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/04 15:08:55 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline uint64_t	get_time_stamp_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

inline uint64_t	get_time_stamp_mc(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000000) + time.tv_usec);
}

inline int32_t	get_relative_time_mc(void)
{
	return ((int32_t)(get_time_stamp_mc() - get_base_time()));
}

inline int32_t	get_relative_time_ms(void)
{
	return ((int32_t)(get_time_stamp_ms() - (get_base_time() / 1000)));
}

inline uint64_t	get_base_time(void)
{
	static uint64_t			val;

	if (val == 0)
		val = get_time_stamp_mc();
	return (val);
}
