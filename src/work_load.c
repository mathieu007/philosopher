/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/18 21:02:36 by math             ###   ########.fr       */
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

int64_t	get_interval(void)
{
	int64_t	interval;
	int64_t	time_to_eat;
	int64_t	num_ph;

	time_to_eat = (int64_t)get_params()->time_to_eat * 1000;
	num_ph = (int64_t)get_params()->num_philo;
	interval = (int64_t)((time_to_eat) / (num_ph / 4));
	return ((int64_t)(interval / 2) - 2);
}

void	start_sim_lweq_800(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	int64_t		end_time;
	int64_t		interval;
	int64_t		time;

	i = 0;
	rev_i = ph_cnt - 2;
	interval = get_interval();
	end_time = get_time_stamp_mc();
	end_time += interval;
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

static void	wait_threads_ready(t_data *data, int32_t ph_cnt)
{
	while (true)
	{
		pthread_mutex_lock(data->write);
		if (data->threads_ready == ph_cnt)
		{
			pthread_mutex_unlock(data->write);
			break ;
		}
		pthread_mutex_unlock(data->write);
	}
}

void	set_philo_start_time(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	int64_t		start_time;
	int64_t		interval;
	t_data		*data;

	i = 0;
	data = get_data();
	rev_i = ph_cnt - 2;
	interval = (get_interval());
	start_time = data->base_time;
	while (i < ph_cnt / 2)
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
		rev_i -= 2;
		i += 2;
	}	
	i = 1;
	rev_i = ph_cnt - 1;
	while (i < ph_cnt / 2)
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
		rev_i -= 2;
		i += 2;
	}
}

void	start_sim_gr_800(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		rev_i;
	int64_t		end_time;
	int64_t		interval;
	int64_t		time;
	t_data		*data;

	i = 0;
	data = get_data();
	rev_i = ph_cnt - 2;
	interval = get_interval();
	wait_threads_ready(data, ph_cnt);
	set_constant64(interval, &(data->interval));
	set_constant64(get_time_stamp_mc() + 200000, &(data->base_time));
	end_time = data->base_time;
	set_philo_start_time(phs, ph_cnt);
	usleep(data->base_time - get_time_stamp_mc());
	while (i < ph_cnt / 2)
	{
		pthread_mutex_unlock(phs[i]->start_simulation);
		end_time += interval;
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
			end_time += interval;
			time = end_time - get_time_stamp_mc();
			if (time > 0)
				usleep(time);
		}
		rev_i -= 2;
		i += 2;
	}	
	i = 1;
	data = get_data();
	rev_i = ph_cnt - 1;
	while (i < ph_cnt / 2)
	{
		pthread_mutex_unlock(phs[i]->start_simulation);
		end_time += interval;
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time);
		if (rev_i > i)
		{
			pthread_mutex_unlock(phs[rev_i]->start_simulation);
			end_time += interval;
			time = end_time - get_time_stamp_mc();
			if (time > 0)
				usleep(time);
		}
		rev_i -= 2;
		i += 2;
	}
}

void	*print_messages(void *val)
{
	t_print_buffer	*buffer;
	t_data			*data;
	static int32_t	ret;

	data = (t_data *)val;
	buffer = data->buffer;
	ret = 0;
	while (true)
	{
		if (print_msg_buffer(data, buffer))
		{
			ret = 1;
			break ;
		}
		usleep(5000);
	}
	return (&ret);
}

void	start_simulation()
{
	t_philo			**phs;
	int32_t			ph_cnt;
	t_data			*data;
	pthread_t		print_thread;

	phs = get_philosophers();
	ph_cnt = get_params()->num_philo;
	if (ph_cnt > 800)
		start_sim_gr_800(phs, ph_cnt);
	else
		start_sim_lweq_800(phs, ph_cnt);
	data = get_data();
	pthread_create(&print_thread, NULL, print_messages, data);
}
