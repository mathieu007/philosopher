/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/04 10:17:17 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_timing(int32_t ph_cnt)
{
	t_data	*data;

	data = get_data();
	wait_threads_ready(data, ph_cnt);
	set_constant64(get_time_stamp_mc() + 200000, &(data->base_time));
	set_philo_start_time(ph_cnt);
	usleep(data->base_time - get_time_stamp_mc() - 10000);
}

static void	dispatch_philos_timing(t_philo **phs, int32_t ph_cnt, int32_t i,
		int32_t rev_i)
{
	while (i <= ph_cnt / 2)
	{
		if (!phs[i]->dispatched)
		{
			phs[i]->dispatched = true;
			sleeper(phs[i]->start_time);
			pthread_mutex_unlock(phs[i]->start_simulation);
		}
		if (rev_i > i)
		{
			if (!phs[rev_i]->dispatched)
			{
				phs[rev_i]->dispatched = true;
				sleeper(phs[rev_i]->start_time);
				pthread_mutex_unlock(phs[rev_i]->start_simulation);
			}
		}
		else
			return ;
		rev_i -= 2;
		i += 2;
	}
}

void	dispatch_philos(t_philo **phs, int32_t ph_cnt)
{
	int32_t	i;
	int32_t	rev_i;

	init_timing(ph_cnt);
	i = 0;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 3;
	else
		rev_i = ph_cnt - 2;
	dispatch_philos_timing(phs, ph_cnt, i, rev_i);
	i = 1;
	if (is_odd(ph_cnt))
		rev_i = ph_cnt - 2;
	else
		rev_i = ph_cnt - 1;
	if (ph_cnt < 4)
		dispatch_philos_timing(phs, 4, i, rev_i);
	else
		dispatch_philos_timing(phs, ph_cnt, i, rev_i);
	if (is_odd(ph_cnt))
		dispatch_philos_timing(phs, ph_cnt * 2, ph_cnt - 1, ph_cnt - 1);
}
