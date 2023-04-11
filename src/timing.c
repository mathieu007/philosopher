/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/10 07:36:57 by math             ###   ########.fr       */
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

inline int32_t	get_relative_time_mc(const t_data *data)
{
	return ((int32_t)(get_time_stamp_mc() - data->base_time));
}

inline int32_t	get_relative_time_ms(const t_data *data)
{
	return (get_relative_time_mc(data) / 1000);
}
