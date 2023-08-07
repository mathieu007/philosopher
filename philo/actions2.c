/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/07 11:18:33 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	eating(t_philo *ph, t_data *data)
{
	save_eat(ph, data);
	if (die_eating(ph, data))
		return ;
	three_stage_sleep(ph, ph->last_meal + ph->time_to_eat);
}

inline void	sleeping(t_philo *ph, t_data *data)
{
	save_msg(" is sleeping\n", ph, data);
	if (die_sleeping(ph, data))
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
