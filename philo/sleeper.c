/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:59:45 by math              #+#    #+#             */
/*   Updated: 2023/08/07 08:35:30 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline int32_t	sleeper_stage1(const t_philo *ph, int32_t time,
	int32_t end_time)
{
	if (time > 10000)
	{
		time -= 10000;
		usleep(time);
		time = end_time - get_relative_time_mc(ph);
	}
	if (time > 5000)
	{
		time -= 5000;
		usleep(time);
		time = end_time - get_relative_time_mc(ph);
	}
	if (time > 2500)
	{
		time -= 2500;
		usleep(time);
		time = end_time - get_relative_time_mc(ph);
	}
	return (time);
}

static inline int32_t	sleeper_stage2(const t_philo *ph, int32_t time,
	int32_t end_time)
{
	if (time > 1250)
	{
		time -= 1250;
		usleep(time);
		time = end_time - get_relative_time_mc(ph);
	}
	if (time > 750)
	{
		time -= 750;
		usleep(time);
		time = end_time - get_relative_time_mc(ph);
	}
	return (time);
}

inline void	three_stage_sleep(const t_philo *ph, int32_t end_time)
{
	int32_t	time;

	time = end_time - get_relative_time_mc(ph);
	time = sleeper_stage1(ph, time, end_time);
	time = sleeper_stage2(ph, time, end_time);
	if (time < 0)
		return ;
	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
}
