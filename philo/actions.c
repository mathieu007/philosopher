/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/07 11:18:46 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline bool	die_sleeping(t_philo *ph, t_data *data)
{
	if ((ph->exit_status == 0
			&& ph->death_time <= ph->last_action + ph->time_to_sleep))
	{
		ph->exit_status = 1;
		three_stage_sleep(ph, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	if (ph->time_to_sleep >= ph->time_to_die)
		return (ph->exit_status = 1, true);
	return (false);
}

inline bool	die_thinking(t_philo *ph, t_data *data)
{
	if (ph->exit_status == 0 && ph->death_time <= ph->last_action
		+ ph->next_time_cycle)
	{
		ph->exit_status = 1;
		three_stage_sleep(ph, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	return (false);
}

inline bool	die_eating(t_philo *ph, t_data *data)
{
	if ((ph->exit_status == 0
			&& ph->death_time <= ph->last_action + ph->time_to_eat))
	{
		ph->exit_status = 1;
		three_stage_sleep(ph, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	if (ph->time_to_eat >= ph->time_to_die)
		return (ph->exit_status = 1, true);
	return (false);
}
