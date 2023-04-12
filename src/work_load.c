/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/12 17:07:36 by mroy             ###   ########.fr       */
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
	interval = (uint64_t)((time_to_eat - 5000) / (num_ph / 4)) + 25;
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

uint64_t	start_sim_odd(t_philo **phs, int32_t ph_cnt, uint64_t end_time)
{
	int32_t		i;
	int32_t		rev_i;
	uint64_t	interval;
	t_data		*data;
	int32_t		time;

	i = 1;
	rev_i = ph_cnt - 1;
	data = get_data();
	interval = get_interval();
	while (i < ph_cnt / 2)
	{		
		pthread_mutex_unlock(phs[i]->start_simulation);
		phs[i]->last_think = end_time - data->base_time;
		time = (end_time - (interval / 2)) - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
			phs[rev_i]->last_think = (end_time + interval / 2) - data->base_time;
		}
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
	return (end_time);
}

uint64_t	start_sim(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	uint64_t	end_time;
	uint64_t	interval;
	t_data		*data;
	int32_t		time;

	i = 0;
	rev_i = ph_cnt - 2;
	data = get_data();
	interval = get_interval();
	end_time = get_time_stamp_mc();
	while (i < ph_cnt / 2)
	{		
		pthread_mutex_unlock(phs[i]->start_simulation);
		phs[i]->last_think = end_time - data->base_time;
		time = (end_time - (interval / 2)) - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
			phs[rev_i]->last_think = (end_time + interval / 2) - data->base_time;
		}
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		end_time += interval;
		rev_i -= 2;
		i += 2;
	}
	return (end_time);
}

void	start_simulation()
{
	int32_t		i;
	int32_t		rev_i;
	t_philo		**phs;
	int32_t		ph_cnt;
	uint64_t	end_time;

	ph_cnt = get_params()->num_philo;
	phs = get_philosophers();
	i = 0;
	rev_i = ph_cnt - 2;
	get_data()->base_time = get_time_stamp_mc();
	end_time = start_sim(phs, ph_cnt);
	start_sim_odd(phs, ph_cnt, end_time);
}
