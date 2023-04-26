/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/26 15:10:08 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	two_stage_sleep(const t_philo *ph, int32_t time_to_sleep,
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
	if (time > 0)
		usleep(time);
}

inline void	eating(t_philo *ph, t_data *data, const int32_t time_to_eat)
{
	ph->last_meal = print_eat(ph, data);
	two_stage_sleep(ph, time_to_eat, ph->last_meal + time_to_eat);
	pthread_mutex_lock(data->write);
	*(ph->left_fork_taken) = false;
	*(ph->right_fork_taken) = false;
	pthread_mutex_unlock(data->write);
}

inline void	sleeping(t_philo *ph, t_data *data,
	const int32_t time_to_sleep)
{
	int32_t			sleep_time;

	sleep_time = print_msg(" is sleeping\n", ph, data);
	two_stage_sleep(ph, time_to_sleep, sleep_time + time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data)
{
	const int32_t	time_cycle = ph->params->time_cycle;

	print_msg(" is thinking\n", ph, data);
	ph->last_think += (int64_t)time_cycle;
	sleeper(ph->last_think);
}
