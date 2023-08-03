/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 20:59:45 by math              #+#    #+#             */
/*   Updated: 2023/08/03 18:17:08 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline int32_t	sleeper_stage1(int32_t time)
{
	if (time > 10000)
	{
		time -= 10000;
		usleep(time);
		time = 5000;
	}
	if (time > 5000)
	{
		time -= 5000;
		usleep(time);
		time = 2500;
	}
	if (time > 2500)
	{
		time -= 2500;
		usleep(time);
		time = 1250;
	}
	return (time);
}

static inline int32_t	sleeper_stage2(int32_t time)
{
	if (time > 1250)
	{
		time -= 1250;
		usleep(time);
		time = 750;
	}
	if (time > 750)
	{
		time -= 750;
		usleep(time);
		time = 375;
	}
	return (time);
}

inline void	three_stage_sleep(const t_philo *ph, int32_t end_time)
{
	int32_t	time;

	time = end_time - get_relative_time_mc(ph);
	time = sleeper_stage1(time);
	time = sleeper_stage2(time);
	if (time < 0)
		return ;
	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
}
