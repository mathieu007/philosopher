/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/05 14:42:09 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	save_die_msg(t_philo *ph, t_data *data)
{	
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
	{
		ph->exit_status = 1;
		ph->last_action = get_relative_time_mc(ph);
		save_to_buffer(" died\n", ph, data->buffer);
		data->buffer->stop_print = true;
		data->buffer->stop_count = data->buffer->count;
	}
	pthread_mutex_unlock(data->write);
}

inline void	save_eat(t_philo *ph, t_data *data, int32_t time_to_die)
{	
	pthread_mutex_lock(data->write);
	*(ph->right_fork_taken) = true;
	*(ph->left_fork_taken) = true;
	if (!data->exit_threads)
	{
		ph->last_action = get_relative_time_mc(ph);
		if (ph->last_action > ph->last_meal + time_to_die)
			save_die_msg(ph, data);
		else
			save_to_buffer(" is eating\n", ph, data->buffer);
	}
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	ph->last_meal = ph->last_action;
}

inline void	save_msg(const char *msg, t_philo *ph, t_data *data)
{	
	pthread_mutex_lock(data->write);
	ph->last_action = get_relative_time_mc(ph);
	if (!data->exit_threads)
		save_to_buffer(msg, ph, data->buffer);
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	
}
