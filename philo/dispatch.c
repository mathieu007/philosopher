/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/19 15:59:28 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	set_philo_timing(int64_t start_time, int32_t ph_cnt,
	int32_t i, int32_t rev_i)
{
	int64_t		interval;
	t_data		*data;
	t_philo		**phs;

	phs = get_philosophers();
	data = get_data();
	interval = (get_interval());

	while (i <= ph_cnt / 2)
	{
		set_constant64(start_time, &(phs[i]->start_time));
		set_constant64(data->base_time, &(phs[i]->base_time));
		start_time += interval;
		if (rev_i > i)
		{
			set_constant64(start_time, &(phs[rev_i]->start_time));
			set_constant64(data->base_time, &(phs[rev_i]->base_time));
			start_time += interval;
		}
		else
			break ;
		rev_i -= 2;
		i += 2;
	}
}

static void	set_philo_start_time(int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	int64_t		start_time;
	t_data		*data;

	i = 0;
	data = get_data();
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 1;
	else
		rev_i = ph_cnt - 2;
	start_time = data->base_time;
	set_philo_timing(start_time, ph_cnt, i, rev_i);
	start_time = data->base_time + (get_params()->time_to_eat * 1000);
	i = 1;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 2;
	else
		rev_i = ph_cnt - 1;
	set_philo_timing(start_time, ph_cnt, i, rev_i);
}

static void	init_timing(int32_t ph_cnt)
{
	int64_t	interval;
	t_data	*data;

	data = get_data();
	interval = get_interval();
	wait_threads_ready(data, ph_cnt);
	set_constant64(interval, &(data->interval));
	set_constant64(get_time_stamp_mc() + 200000, &(data->base_time));
	set_philo_start_time(ph_cnt);
	usleep(data->base_time - get_time_stamp_mc());
}

static void	dispatch_philos_timing(t_philo **phs, int32_t ph_cnt,
	int32_t i, int32_t rev_i)
{
	int64_t		time;

	while (i <= ph_cnt / 2)
	{
		pthread_mutex_unlock(phs[i]->start_simulation);
		time = phs[i]->start_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
			time = phs[i]->start_time - get_time_stamp_mc();
			if (time > 0)
				usleep(time);
		}
		else
			break ;
		rev_i -= 2;
		i += 2;
	}
}

void	dispatch_philos(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;	

	init_timing(ph_cnt);
	i = 0;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 1;
	else
		rev_i = ph_cnt - 2;
	dispatch_philos_timing(phs, ph_cnt, i, rev_i);
	i = 1;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 2;
	else
		rev_i = ph_cnt - 1;
	dispatch_philos_timing(phs, ph_cnt, i, rev_i);
}
