/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:59:45 by math              #+#    #+#             */
/*   Updated: 2023/07/30 20:59:47 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	three_stage_sleep(const t_philo *ph, int32_t end_time)
{
	int32_t	time;

	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
	{
		if (time > 10000)
			usleep(time - 10000);
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
		else
			return ;
	}
	else
		return ;
	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
}

static inline void	think_sleeper(const t_philo *ph, int32_t end_time)
{
	int32_t	time;

	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
	else
		return ;
}

inline int32_t	two_stage_sleep(const t_philo *ph, int32_t time_to_sleep,
		int32_t end_time)
{
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
	}
	return (time);
}
