/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/21 10:34:00 by mroy             ###   ########.fr       */
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
	int32_t	time_to_think;

	time_to_think = get_params()->time_to_think * 1000;
	time_to_eat = (int64_t)get_params()->time_to_eat * 1000;
	num_ph = (int64_t)get_params()->num_philo - 1;
	if (num_ph < 4)
		num_ph = 4;
	interval = (int64_t)((time_to_eat) / (num_ph / 4));
	if (interval > ((time_to_think / 2) - (time_to_think / 10)) / 2)
		interval = ((time_to_think / 2) - (time_to_think / 10)) / 2;
	return ((int64_t)((interval / 2)));
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
		{
			ret = 1;
			break ;
		}
		usleep(4000);
	}
	return (&ret);
}

void	start_simulation(void)
{
	t_philo		**phs;
	int32_t		ph_cnt;
	t_data		*data;
	pthread_t	print_thread;

	data = get_data();
	phs = get_philosophers();
	ph_cnt = get_params()->num_philo;
	dispatch_philos(phs, ph_cnt);
	pthread_create(&print_thread, NULL, print_messages, data);
	data->buffer->thread_id = print_thread;
}
