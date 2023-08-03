/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/03 12:50:11 by mroy             ###   ########.fr       */
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
	int64_t	time_to_think;
	int64_t	num_ph;
	t_param	*params;

	params = get_params();
	time_to_think = (int64_t)params->time_to_think * 1000;
	time_to_eat = (int64_t)params->time_to_eat * 1000;
	num_ph = (int64_t)params->num_philo - 1;
	if (num_ph < 4)
		num_ph = 4;
	interval = ((time_to_eat - 1000) / (num_ph / 2));
	if (interval > 2000 || interval > time_to_think / 5 
		|| time_to_eat > params->time_to_die * 1000)
		interval = 1000;
	return (interval);
}

void	*print_messages(void *val)
{
	t_data			*data;
	static int32_t	ret;

	data = (t_data *)val;
	ret = 0;
	while (true)
	{
		if (print_msg_buffer(data))
			return (ret = 1, &ret);
		usleep(SLEEP_BUFFER);
	}
	return (&ret);
}

void	*start_simulation(void)
{
	t_philo		**phs;
	int32_t		ph_cnt;
	t_data		*data;
	pthread_t	print_thread;

	data = get_data();
	phs = get_philosophers();
	ph_cnt = get_params()->num_philo;
	dispatch_philos(phs, ph_cnt);
	if (pthread_create(&print_thread, NULL, print_messages, data) != 0)
		return (NULL);
	data->buffer->thread_id = print_thread;
	return (data->buffer);
}
