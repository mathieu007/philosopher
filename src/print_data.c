/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/12 13:57:28 by mroy             ###   ########.fr       */
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

inline void	print_msg_or_die(t_philo *ph, t_data *data)
{	
	const int32_t	time_to_die = ph->params->time_to_die * 1000;
	int32_t			prev_meal;
	
	prev_meal = ph->last_meal;
	pthread_mutex_lock(data->write);
	ph->last_meal = get_relative_time_mc(data);
	if (time_to_die < ph->last_meal - prev_meal)
	{
		if (!data->exit_threads)
		{
			printf("%i %i died\n", ph->last_meal / 1000, ph->name);
			data->exit_threads = true;
		}			
		ph->exit_status = 1;
	}
	else if (!data->exit_threads)
		printf("%i %i is eating\n", ph->last_meal / 1000, ph->name);
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
}


int32_t	print_msg(const char *msg, t_philo *ph, const t_data *data)
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
