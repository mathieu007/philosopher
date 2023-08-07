/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/07 10:27:34 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	set_philo_timing(int64_t start_time, t_philo *ph, const t_data *data,
		const t_param *params)
{
	set_constant64(start_time, &(ph->start_time));
	set_constant64(data->base_time, &(ph->base_time));
	set_constant(data->params->time_to_die * 1000, &(ph->time_to_die));
	set_constant(data->params->time_to_eat * 1000, &(ph->time_to_eat));
	set_constant(data->params->time_to_sleep * 1000, &(ph->time_to_sleep));
	set_constant(data->params->time_to_think * 1000, &(ph->time_to_think));
	if (is_odd(params->num_philo))
		set_constant((ph->time_to_eat * 3) - ph->time_to_eat
			- ph->time_to_sleep, &(ph->next_time_cycle));
	else
		set_constant((ph->time_to_eat * 2) - ph->time_to_eat
			- ph->time_to_sleep, &(ph->next_time_cycle));
	ph->last_meal = (int32_t)(start_time - data->base_time
			- (params->time_to_eat - params->time_to_sleep) * 1000);
	ph->last_action = (int32_t)(start_time - data->base_time
			- (params->time_to_eat - params->time_to_sleep) * 1000);
}

int64_t	set_philos_timing(int64_t start_time, int32_t ph_cnt, int32_t i,
		int32_t rev_i)
{
	int64_t			interval;
	t_philo			**phs;
	const t_param	*params;
	const t_data	*data;

	params = get_params();
	data = get_data();
	phs = get_philosophers();
	interval = get_interval();
	while (i <= ph_cnt / 2)
	{
		set_philo_timing(start_time, phs[i], data, params);
		start_time += interval;
		if (rev_i > i)
		{
			set_philo_timing(start_time, phs[rev_i], data, params);
			start_time += interval;
		}
		else
			return (start_time);
		i += 2;
		rev_i -= 2;
	}
	return (start_time);
}

int32_t	set_even_index(int32_t ph_cnt)
{
	if (is_odd(ph_cnt))
		return (ph_cnt - 3);
	return (ph_cnt - 2);
}

int32_t	set_odd_index(int32_t ph_cnt)
{
	if (is_odd(ph_cnt))
		return (ph_cnt - 2);
	return (ph_cnt - 1);
}

int64_t	set_timings(int32_t ph_cnt, int32_t i, int32_t rev_i,
		int64_t start_time)
{
	t_param	*params;
	int32_t	interval;

	params = get_params();
	interval = get_interval();
	start_time += interval;
	if (params->time_to_die > params->time_to_eat)
	{
		start_time = start_time + (params->time_to_eat * 1000);
		set_philos_timing(start_time, ph_cnt, i, rev_i);
	}
	else
		start_time = set_philos_timing(start_time, ph_cnt, i, rev_i);
	return (start_time);
}
