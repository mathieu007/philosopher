/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/11 19:32:08 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	print_die_msg(const char *msg, t_philo *ph, t_data *data)
{	
	int32_t	time;

	time = 0;
	ph->exit_status = 1;
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		data->exit_threads = true;
		time = get_relative_time_mc(data);
		printf(msg, time / 1000, ph->name);
	}
	pthread_mutex_unlock(data->write);
	return (time);
}

int32_t	print_msg(const char *msg, t_philo *ph, t_data *data)
{	
	int32_t	time;

	time = 0;
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		time = get_relative_time_mc(data);
		printf(msg, time / 1000, ph->name);
	}
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	return (time);
}
