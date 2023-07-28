/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_msg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/28 11:00:19 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	save_die_msg(t_philo *ph, t_data *data)
{
	if (!data->exit_threads)
	{
		ph->exit_status = 1;
		ph->last_action = get_relative_time_mc(ph);
		save_to_buffer(" died\n", ph, data->buffer);
		data->buffer->stop_print = true;
		data->buffer->stop_count = data->buffer->count;
	}
}

inline void	save_or_die(t_philo *ph, t_data *data, const char *msg)
{
	ph->last_action = get_relative_time_mc(ph);
	if (ph->last_action > ph->death_time)
		save_die_msg(ph, data);
	else
		save_to_buffer(msg, ph, data->buffer);
}

inline void	save_eat(t_philo *ph, t_data *data)
{
	if (ph->exit_status == 1)
		return ;
	pthread_mutex_lock(data->write);
	*(ph->right_fork_taken) = true;
	*(ph->left_fork_taken) = true;
	if (!data->exit_threads)
		save_or_die(ph, data, " is eating\n");
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
	ph->last_meal = ph->last_action;
	ph->death_time = ph->last_meal + ph->time_to_die;
}

inline void	save_msg(const char *msg, t_philo *ph, t_data *data)
{
	if (ph->exit_status == 1)
		return ;
	pthread_mutex_lock(data->write);
	if (!data->exit_threads)
		save_or_die(ph, data, msg);
	else
		ph->exit_status = 1;
	pthread_mutex_unlock(data->write);
}
