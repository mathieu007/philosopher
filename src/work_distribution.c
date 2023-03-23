/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_distribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 13:38:41 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline static uint64_t	authorize_forks_take(t_philo **phs,
	int32_t i, uint64_t last_meal, int32_t ph_cnt)
{
	pthread_mutex_lock(phs[i]->left_fork_auth);
	phs[prev_ph(i, ph_cnt)]->is_authorized = false;
	pthread_mutex_unlock(phs[i]->left_fork_auth);
	pthread_mutex_lock(phs[i]->right_fork_auth);	
	phs[next_ph(i, ph_cnt)]->is_authorized = false;
	pthread_mutex_unlock(phs[i]->right_fork_auth);
	phs[i]->is_authorized = true;
	if (phs[i]->last_meal > last_meal)
		return (phs[i]->last_meal);
	return (last_meal);
}

inline static void	work_sleep(uint64_t last_meal)
{
	uint64_t	wait_time;

	wait_time = (((get_params()->time_to_eat + get_params()->time_to_sleep))
			- (get_time_stamp() - last_meal) * 1000) - 1000;
	if (wait_time < 0)
		return ;
	usleep(wait_time);
}

static void	work_loop(t_philo **phs, const int32_t ph_cnt, uint64_t last_meal)
{
	int32_t		i;
	t_philo		*ph;

	i = 0;
	while (i < ph_cnt)
	{
		ph = phs[i];
		if (phs[next_ph(i, ph_cnt)]->is_authorized)
			i += 3;
		else if (ph->is_authorized)
			i += 2;
		else if (phs[prev_ph(i, ph_cnt)]->is_authorized)
			i++;
		else if (ph->last_meal <= phs[prev_ph(i, ph_cnt)]->last_meal
			&& ph->last_meal <= phs[next_ph(i, ph_cnt)]->last_meal)
		{
			last_meal = authorize_forks_take(phs, i, last_meal, ph_cnt);
			i += 2;
		}
		else
			i++;
	}
	work_sleep(last_meal);
}

void	work_distribution(void)
{
	t_philo			**phs;
	const int32_t	ph_cnt = get_params()->num_philo;
	uint64_t		last_meal;

	last_meal = 0;
	phs = get_philosophers();
	while (true)
		work_loop(phs, ph_cnt, last_meal);
}
