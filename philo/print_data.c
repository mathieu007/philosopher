/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/20 12:13:08 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	print_die_msg(const char *msg, t_philo *ph, t_data *data)
{	
	int32_t					time;

	time = 0;
	ph->exit_status = 1;
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		data->exit_threads = true;
		time = get_relative_time_mc(ph);
		printf(msg, time / 1000, ph->name);
	}
	pthread_mutex_unlock(data->write);
	return (time);
}

inline int32_t	print_eat_or_die(t_philo *ph, t_data *data, int32_t prev_meal)
{	
	int32_t			time;
	const int32_t	time_to_die = ph->params->time_to_die * 1000;

	time = get_relative_time_mc(ph);
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		if (time_to_die < time - prev_meal)
		{
			ph->exit_status = 1;
			data->exit_threads = true;
			data->buffer->exit = true;
			save_msg(" died\n", time / 1000, ph->name, data->buffer);
		}
		else
			save_msg(" is eating\n", time / 1000, ph->name, data->buffer);
	}
	else
	{
		ph->exit_status = 1;
		data->buffer->exit = true;
	}
	pthread_mutex_unlock(data->write);
	return (time);
}

inline int32_t	print_msg(const char *msg, t_philo *ph, t_data *data)
{	
	int32_t					time;

	time = 0;
	time = get_relative_time_mc(ph);
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		save_msg(msg, time / 1000, ph->name, data->buffer);
	}
	else
	{
		ph->exit_status = 1;
		data->buffer->exit = true;
	}
	pthread_mutex_unlock(data->write);
	return (time);
}
