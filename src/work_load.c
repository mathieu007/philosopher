/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/11 20:06:56 by math             ###   ########.fr       */
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
		pthread_mutex_lock(phs[i]->start_simulation);
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

void	start_sim_lweq_800(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	uint64_t	end_time;
	uint64_t	interval;
	uint64_t	time;

	i = 0;
	rev_i = ph_cnt - 2;
	interval = get_interval();
	end_time = get_time_stamp_mc() + interval;
	while (i < ph_cnt / 2)
	{
		pthread_mutex_unlock(phs[i]->start_simulation);
		usleep(50);
		if (rev_i > i)
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
}

void	start_sim_gr_800(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	uint64_t	end_time;
	uint64_t	interval;
	uint64_t	time;

	i = 0;
	rev_i = ph_cnt - 2;
	interval = get_interval();
	end_time = get_time_stamp_mc() + interval;
	while (i < ph_cnt / 2)
	{
		pthread_mutex_unlock(phs[i]->start_simulation);
		if (rev_i > i)
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
}

void	start_simulation(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;

	i = 0;
	rev_i = ph_cnt - 2;
	get_data()->base_time = get_time_stamp_mc();
	if (ph_cnt > 800)
		start_sim_gr_800(phs, ph_cnt);
	else
		start_sim_lweq_800(phs, ph_cnt);
	i = 1;
	rev_i = ph_cnt - 1;
	while (i < ph_cnt / 2)
	{	
		pthread_mutex_unlock(phs[i]->start_simulation);
		if (rev_i > i)
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
		rev_i -= 2;
		i += 2;
	}
}
