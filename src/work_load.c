/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/13 16:59:05 by mroy             ###   ########.fr       */
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
		phs[i]->is_auth = false;
		pthread_mutex_lock(phs[i]->process_mutex);
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

bool	dispatch_odd_process(t_philo **phs, const int32_t ph_cnt, const int32_t max)
{
	int32_t			i;	
	int32_t			rev_i;
	int64_t			time;
	const int32_t	time_cycle = get_params()->time_cycle;

	i = 0;
	rev_i = ph_cnt - 2;
	while (i < max)
	{
		phs[i]->last_think += time_cycle;
		time = phs[i]->last_think - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		pthread_mutex_unlock(phs[i]->process_mutex);
		usleep(10);
		pthread_mutex_lock(phs[i]->process_mutex);
		if (rev_i > i)
		{
			phs[rev_i]->last_think += time_cycle;
			time = phs[rev_i]->last_think - get_time_stamp_mc();
			if (time > 0)
				usleep(time);
			pthread_mutex_unlock(phs[rev_i]->process_mutex);
			usleep(10);
			pthread_mutex_lock(phs[rev_i]->process_mutex);
		}
		rev_i -= 2;
		i += 2;
	}
	return (false);
}

bool	dispatch_even_process(t_philo **phs, const int32_t ph_cnt, const int32_t max)
{
	int32_t			i;	
	int32_t			rev_i;
	int64_t			time;
	const int32_t	time_cycle = get_params()->time_cycle;

	i = 1;
	rev_i = ph_cnt - 1;
	time = 0;
	while (i < max)
	{
		phs[i]->last_think += time_cycle;
		time = phs[i]->last_think - get_time_stamp_mc() - 500;
		if (time > 0)
			usleep(time);
		pthread_mutex_unlock(phs[i]->process_mutex);
		usleep(10);
		pthread_mutex_lock(phs[i]->process_mutex);
		if (rev_i > i)
		{
			phs[rev_i]->last_think += time_cycle;
			time = phs[rev_i]->last_think - get_time_stamp_mc() - 500;
			if (time > 0)
				usleep(time);
			pthread_mutex_unlock(phs[rev_i]->process_mutex);
			usleep(10);
			pthread_mutex_lock(phs[rev_i]->process_mutex);
		}
		rev_i -= 2;
		i += 2;
	}
	return (false);
}


int64_t	start_odd_process(t_philo **phs, const int32_t ph_cnt, const uint64_t interval, const int32_t max)
{
	int32_t			i;	
	int64_t			time;
	int32_t			rev_i;
	int64_t			sleep_limit;

	i = 0;
	rev_i = ph_cnt - 2;
	sleep_limit = get_time_stamp_mc();
	time = 0;
	while (i < max)
	{
		pthread_mutex_unlock(phs[i]->process_mutex);
		phs[i]->last_think = sleep_limit;
		usleep(10);
		pthread_mutex_lock(phs[i]->process_mutex);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->process_mutex);
			phs[rev_i]->last_think = sleep_limit;
			usleep(10);
			pthread_mutex_lock(phs[rev_i]->process_mutex);
		}
		sleep_limit += interval;
		time = sleep_limit - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		rev_i -= 2;
		i += 2;
	}
	return (sleep_limit);
}

void	start_even_process(int64_t sleep_limit, const int32_t ph_cnt, const uint64_t interval, const int32_t max)
{
	int32_t			i;	
	int64_t			time;
	int32_t			rev_i;
	t_philo			**phs;

	i = 1;
	phs = get_philosophers();
	rev_i = ph_cnt - 1;
	time = 0;
	while (i < max)
	{
		pthread_mutex_unlock(phs[i]->process_mutex);
		phs[i]->last_think = sleep_limit;
		usleep(10);
		pthread_mutex_lock(phs[i]->process_mutex);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->process_mutex);
			phs[rev_i]->last_think = sleep_limit;
			usleep(10);
			pthread_mutex_lock(phs[rev_i]->process_mutex);
		}
		sleep_limit += interval;
		time = sleep_limit - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		rev_i -= 2;
		i += 2;
	}
}

void	sync_workload(t_philo **phs, const int32_t ph_cnt, const int32_t max)
{
	if (!dispatch_odd_process(phs, ph_cnt, max) || !dispatch_even_process(phs, ph_cnt, max))
		sync_workload(phs, ph_cnt, max);
}

void	unlock_work(t_philo **phs, const int32_t ph_cnt, const int32_t max, const uint64_t interval)
{
	int64_t	sleep_limit;

	get_data()->base_time = get_time_stamp_mc();
	sleep_limit = start_odd_process(phs, ph_cnt, interval, max);
	start_even_process(sleep_limit, ph_cnt, interval, max);
}

void	start_simulation(int32_t ph_cnt)
{
	const uint64_t	interval = 3900;
	t_philo			**phs;
	int32_t			max;

	phs = get_philosophers();
	max = ph_cnt / 2;
	
	unlock_work(get_philosophers(), ph_cnt, max, interval);
	sync_workload(phs, ph_cnt, max);
}
