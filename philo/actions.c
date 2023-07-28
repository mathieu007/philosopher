/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/27 15:42:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	three_stage_sleep(int64_t time_to_sleep, int64_t end_time)
{	
	int64_t	time;

	time = time_to_sleep - 10000;
	if (time > 0)
		usleep(time);
	time = end_time - get_time_stamp_mc();
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	if (time > 0)
		usleep(time);
}

static inline void	think_sleeper(int64_t end_time)
{	
	int64_t	time;

	time = (end_time - get_time_stamp_mc());
	if (time > 0)
	{
		usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	if (time > 0)
		usleep(time);
}

inline int64_t	two_stage_sleep(int64_t time_to_sleep, int64_t end_time)
{
	int64_t	time;

	time = time_to_sleep - 10000;
	if (time > 0)
	{
		usleep(time);
		time = end_time - get_time_stamp_mc();
	}
	while (time - 500 > 0)
	{
		if (time > 500)
			usleep(time / 2);
		time = end_time - get_time_stamp_mc();
	}
	return (time);
}

inline void	eating(t_philo *ph, t_data *data, int64_t time_to_eat, const int64_t time_to_die)
{
	int64_t	time;
	int64_t	last_action;

	last_action = save_eat(ph, data, time_to_die);
	time = two_stage_sleep(time_to_eat, (last_action + time_to_eat));
	if (time > 0)
		usleep(time);
}

inline void	sleeping(t_philo *ph, t_data *data, int64_t time_to_sleep)
{
	int64_t	last_action;

	last_action = save_msg(" is sleeping\n", SLEEP_MSG_LEN, ph, data);
	three_stage_sleep(time_to_sleep, last_action + time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data)
{
	const int64_t	time_cycle = ph->params->time_cycle;

	save_msg(" is thinking\n", THINK_MSG_LEN, ph, data);
	ph->last_think += time_cycle;
	think_sleeper(ph->last_think - ph->base_time);
}
