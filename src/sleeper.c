/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 09:09:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline second_stage_sleeper(int32_t sleep_time, bool (*exec)())
{
	int32_t time_left;
	int32_t true_time_left;

	true_time_left = gettimeofday();
	while (true_time_left > 1)
	{
		if (exec())
		{
			
		}
		usleep(1);
		true_time_left--;
	}
}
/// @brief the wait_time is spleep_time | think_time
/// @param wait_time 
/// @param exec 
inline void	sleep_exec(int32_t wait_time, bool (*exec)())
{
	t_param	*param;
	int32_t	i;
	int32_t	time_per_sleep;
	int32_t	min_sleep;

	if (wait_time <= 10)
	{
		
	}
	time_per_sleep = 
	i = 0;
	while (usleep() )
}

void	init_dispatchers(void)
{
	pthread_t	*threads;

	threads = get_thread();
	memset(threads, 0, MAX_PHILOSOPHER);
}

