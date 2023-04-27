/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/26 16:21:42 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	print_die_msg(t_philo *ph, t_data *data)
{	
	int32_t			time;

	pthread_mutex_lock(data->write);
	time = get_relative_time_mc(ph);
	if (!data->exit_threads)
	{
		ph->exit_status = 1;
		save_dead_msg(" died\n", time / 1000, ph, data->buffer);
	}
	pthread_mutex_unlock(data->write);
	return (time);
}

inline int32_t	print_eat(t_philo *ph, t_data *data)
{	
	int32_t		time;

	pthread_mutex_lock(data->write);
	*(ph->right_fork_taken) = true;
	*(ph->left_fork_taken) = true;
	time = get_relative_time_mc(ph);
	if (!data->exit_threads)
		save_msg(" is eating\n", time / 1000, ph, data->buffer);
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	return (time);
}

inline int32_t	print_msg(const char *msg, t_philo *ph, t_data *data)
{	
	int32_t					time;

	time = 0;
	pthread_mutex_lock(data->write);
	time = get_relative_time_mc(ph);
	if (!data->exit_threads)
		save_msg(msg, time / 1000, ph, data->buffer);
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	return (time);
}
