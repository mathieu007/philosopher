/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/27 19:02:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	lock_all_philos(void)
{
	int32_t			i;
	const int64_t	ph_cnt = get_params()->num_philo;
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
	int64_t	num_ph;

	num_ph = (int64_t)get_params()->num_philo - 1;
	if (num_ph < 4)
		num_ph = 4;
	interval = (int64_t)get_params()->time_cycle / num_ph;
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
		{
			ret = 1;
			break ;
		}
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
