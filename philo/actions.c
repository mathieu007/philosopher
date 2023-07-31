/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/31 11:00:07 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline bool	die_in_action(t_philo *ph, t_data *data, int32_t action_time)
{
	if (ph->exit_status == 0 && ph->death_time < ph->last_action + action_time)
	{
		three_stage_sleep(ph, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	return (false);
}

inline bool	die_thinking(t_philo *ph, t_data *data)
{
	if (ph->exit_status == 0 && ph->death_time < ph->last_action
		+ ph->next_time_cycle)
	{
		three_stage_sleep(ph, ph->death_time);
		pthread_mutex_lock(data->write);
		save_die_msg(ph, data);
		pthread_mutex_unlock(data->write);
		return (true);
	}
	return (false);
}

inline void	eating(t_philo *ph, t_data *data)
{
	save_eat(ph, data);
	if (die_in_action(ph, data, ph->time_to_eat))
		return ;
	three_stage_sleep(ph, ph->last_meal + ph->time_to_eat);
}

inline void	sleeping(t_philo *ph, t_data *data)
{
	save_msg(" is sleeping\n", ph, data);
	if (die_in_action(ph, data, ph->time_to_sleep))
		return ;
	three_stage_sleep(ph, ph->last_action + ph->time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data)
{
	const int32_t	time_cycle = ph->params->time_cycle;

	save_msg(" is thinking\n", ph, data);
	if (die_thinking(ph, data))
		return ;
	ph->last_think += (int64_t)time_cycle;
	three_stage_sleep(ph, (int32_t)ph->last_think - ph->base_time);
}
