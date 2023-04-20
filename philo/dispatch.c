/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/20 13:48:09 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


static void	set_philo_timing(int64_t start_time, t_philo *ph,
	const t_data *data, const t_param *params)
{
	set_constant64(start_time, &(ph->start_time));
	set_constant64(data->base_time, &(ph->base_time));
	set_constant((int32_t)(start_time - data->base_time - (params->time_to_eat
				- params->time_to_sleep) * 1000), &(ph->last_meal));
}

static void	set_philos_timing(int64_t start_time, int32_t ph_cnt, int32_t i,
	int32_t rev_i)
{
	int64_t			interval;
	t_philo			**phs;
	const t_param	*params = get_params();
	const t_data	*data = get_data();

	phs = get_philosophers();
	interval = get_interval();
	while (i <= ph_cnt / 2)
	{
		set_philo_timing(start_time, phs[i], data, params);
		start_time += interval;
		if (rev_i > i)
		{
			set_philo_timing(start_time, phs[rev_i], data, params);
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
	t_param		*params;
	t_philo		**phs;

	i = 0;
	phs = get_philosophers();
	params = get_params();
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 3;
	else
		rev_i = ph_cnt - 2;
	start_time = get_data()->base_time;
	set_philos_timing(start_time, ph_cnt, i, rev_i);
	start_time = start_time + (params->time_to_eat * 1000);
	i = 1;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 2;
	else
		rev_i = ph_cnt - 1;
	set_philos_timing(start_time, ph_cnt, i, rev_i);
	if (is_odd(ph_cnt))
	{
		start_time = start_time + (params->time_to_eat * 1000);
		set_philo_timing(start_time, phs[ph_cnt - 1], get_data(), params);
	}
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
	usleep(data->base_time - get_time_stamp_mc() - 10000);
}

static void	dispatch_philos_timing(t_philo **phs, int32_t ph_cnt,
	int32_t i, int32_t rev_i)
{
	int64_t		time;

	time = phs[i]->start_time - get_time_stamp_mc();
	if (time > 0)
		usleep(time);
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
		rev_i = ph_cnt - 3;
	else
		rev_i = ph_cnt - 2;
	dispatch_philos_timing(phs, ph_cnt, i, rev_i);
	i = 1;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 2;
	else
		rev_i = ph_cnt - 1;
	dispatch_philos_timing(phs, ph_cnt, i, rev_i);
	if (is_odd(ph_cnt))
		dispatch_philos_timing(phs, ph_cnt * 2, ph_cnt - 1, ph_cnt - 1);
}
