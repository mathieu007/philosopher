/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 07:19:32 by math             ###   ########.fr       */
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
	static uint64_t	base_time;

	if (base_time == 0)
		base_time = (*get_thread_philo())->base_time;
	return ((int32_t)(get_time_stamp_mc() - base_time));
}

inline int32_t	get_relative_time_ms(void)
{
	return (get_relative_time_mc() / 1000);
}
