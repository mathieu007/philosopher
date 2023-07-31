/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/30 20:59:12 by math             ###   ########.fr       */
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
	if (die_in_action(ph, data, ph->next_time_cycle))
		return ;
	ph->last_think += (int64_t)time_cycle;
	think_sleeper(ph, (int32_t)(ph->last_think - ph->base_time));
}
