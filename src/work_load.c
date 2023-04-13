/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/13 07:37:59 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	lock_all_philos(void)
{
	int32_t			i;
	const int32_t	ph_cnt = get_params()->num_philo;
	t_philo			**phs;

	phs = get_philosophers();
	i = 0;
	while (i < ph_cnt)
	{	
		pthread_mutex_lock(phs[i]->auth_forks);
		i++;
	}
}

uint64_t	get_interval(void)
{
	uint64_t	interval;
	uint64_t	time_to_eat;
	uint64_t	time_to_think;
	uint64_t	num_ph;
	uint64_t	limit;

	time_to_eat = (uint64_t)get_params()->time_to_eat * 1000;
	time_to_think = (uint64_t)get_params()->time_to_think * 1000;
	num_ph = (uint64_t)get_params()->num_philo;
	interval = (uint64_t)((time_to_eat - 5000) / (num_ph / 4));
	limit = ((time_to_think) / 2) - time_to_think / 7;
	if (interval >= limit)
		interval = limit;
	return (interval);
}

void	start_workload(t_philo **phs, int32_t ph_cnt, uint64_t end_time, const uint64_t	interval)
{
	int32_t			i;
	int32_t			rev_i;
	uint64_t		time;
	int32_t			max;
	const int32_t	time_cycle = get_params()->time_to_die - (get_params()->time_to_think / 2);

	i = 0;
	rev_i = ph_cnt - 2;
	max = ph_cnt / 2;
	while (i < max)
	{
		pthread_mutex_lock(phs[i]->process_mutex);
		time = phs[i]->last_think - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		pthread_mutex_unlock(phs[i]->process_mutex);
		pthread_mutex_lock(phs[rev_i]->process_mutex);
		time = phs[rev_i]->last_think - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		pthread_mutex_unlock(phs[rev_i]->process_mutex);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
	i = 1;
	rev_i = ph_cnt - 1;
	while (i < max)
	{
		pthread_mutex_unlock(phs[i]->auth_forks);
		if (rev_i > i)
			pthread_mutex_unlock(phs[rev_i]->auth_forks);
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		pthread_mutex_lock(phs[i]->auth_forks);
		pthread_mutex_lock(phs[rev_i]->auth_forks);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
	// time = (start_time + time_cycle) - get_time_stamp_mc();
	// if (time > 0)
	// 	usleep(time);
		
	start_workload(phs, ph_cnt, end_time, interval);
}

void	start_simulation(int32_t ph_cnt)
{
	uint64_t		end_time;
	const uint64_t	interval = 2000;

	get_data()->base_time = get_time_stamp_mc();
	end_time = get_time_stamp_mc() + interval;
	start_workload(get_philosophers(), ph_cnt, end_time, interval);
}
