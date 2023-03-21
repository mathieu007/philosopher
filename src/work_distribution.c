/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 21:09:02 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_dispatcher	*get_dispatchers(void)
{
	static t_dispatcher	dispatchers[MAX_PHILOSOPHER];

	return (&dispatchers[0]);
}

void	init_dispatchers(void)
{
	t_dispatcher	*dispatchers;

	dispatchers = get_dispatcher();
	memset(dispatchers, 0, MAX_PHILOSOPHER);
}

void	authorize_forks_take(t_philo *ph)
{
	pthread_mutex_lock(ph->take_forks);
	ph->priority = true;
	pthread_mutex_unlock(ph->take_forks);
}

static void	dispatch_work_loop(t_philo **phs, const int32_t ph_cnt)
{
	t_philo	*ph;
	t_philo	*nxt_ph;
	t_philo	*prv_ph;
	int32_t	i;

	i = 0;
	while (i < ph_cnt)
	{
		ph = phs[i];
		nxt_ph = phs[next_ph(i, ph_cnt)];
		prv_ph = phs[prev_ph(i, ph_cnt)];
		if (nxt_ph->priority)
			i += 3;
		else if (ph->priority)
			i += 2;
		else if (prv_ph->priority)
			i++;
		else if (ph->last_meal <= prv_ph->last_meal && ph->last_meal <= nxt_ph->last_meal)
		{
			authorize_forks_take(ph);
			i += 2;
		}
		else
			i++;
	}
}

void	dispatch_work_distrib(void)
{
	t_philo			**phs;
	const int32_t	ph_cnt = get_params()->num_philo;

	phs = get_philosophers();
	while (true)
	{
		dispatch_work_loop(phs, ph_cnt);
		if (usleep(1) != 0)
			return (free_all());
	}
}
