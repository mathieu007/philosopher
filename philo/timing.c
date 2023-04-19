/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/14 15:27:11 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int64_t	get_time_stamp_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int64_t)1000) + (time.tv_usec / 1000));
}

inline int64_t	get_time_stamp_mc(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (int64_t)1000000) + time.tv_usec);
}

inline int32_t	get_relative_time_mc(const t_philo *ph)
{
	return ((int32_t)(get_time_stamp_mc() - ph->base_time));
}

inline int32_t	get_relative_time_ms(const t_philo *ph)
{
	return (get_relative_time_mc(ph) / 1000);
}
