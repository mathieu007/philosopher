/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 07:09:38 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	authorize_forks_take(t_philo *ph)
{
	pthread_mutex_unlock(ph->forks_auth);
	while (true)
	{	
		usleep(1);
		if (ph->forks_taken)
		{
			pthread_mutex_lock(ph->forks_auth);
			break ;
		}
	}
}

// static void	update_forks_take(t_philo *ph)
// {
// 	pthread_mutex_unlock(ph->forks_take);
// 	while (true)
// 	{		
// 		if (ph->forks_taken)
// 		{
// 			pthread_mutex_lock(ph->forks_take);
// 			break ;
// 		}
// 	}
// }

inline static void	work_sleep(int32_t wait_time)
{
	if (wait_time < 0)
		return ;
	usleep(wait_time);
}
/// @brief linux
/// @param tail 
/// @param prev_tail 
/// @return 
// static inline bool	should_swap(void *tail, void *prev_tail)
// {
// 	if (((t_philo *)tail)->last_meal > ((t_philo *)prev_tail)->last_meal)
// 		return (true);
// 	return (false);
// }

static void	process_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	// t_philo			*ph2;
	t_philo			*ph_next;
	t_philo			*ph_prev;
	static t_fifo	*wait_fifo;

	if (wait_fifo == NULL)
		wait_fifo = get_data()->wait_queue;
	while (true)
	{	
		ph = (t_philo *)fifo_concurent_get_pop(wait_fifo);
		if (ph == NULL)
		{
			usleep(1);
			continue ;
		}
		//fifo_concurrent_swap_tail(wait_fifo, ph, &should_swap);
		ph_next = phs[next_ph(ph->position, ph_cnt)];
		ph_prev = phs[prev_ph(ph->position, ph_cnt)];
		while (ph->forks_taken || ph_next->forks_taken || ph_prev->forks_taken)
			usleep(1);
		authorize_forks_take(ph);
	}
}

static void	work_loop(t_philo **phs, int32_t ph_cnt)
{
	int32_t	li;
	int32_t	ri;
	t_fifo	*wait_fifo;
	int32_t	max;

	li = 0;
	ri = ph_cnt - 2;
	wait_fifo = get_data()->wait_queue;
	max = ph_cnt / 2;
	while (li < max)
	{
		fifo_put(wait_fifo, (void *)phs[li]);
		if (li != ri)
		{
			fifo_put(wait_fifo, (void *)phs[ri]);
			ri -= 2;
		}
		li += 2;
	}
	li = 1;
	ri = ph_cnt - 1;
	while (li < max)
	{
		fifo_put(wait_fifo, (void *)phs[li]);
		if (li != ri)
		{
			fifo_put(wait_fifo, (void *)phs[ri]);
			ri -= 2;
		}
		li += 2;
	}
	process_wait_list(phs, ph_cnt);
}


void	lock_all_philos(void)
{
	int32_t			i;
	const int32_t	ph_cnt = get_params()->num_philo;
	t_philo			**phs;

	phs = get_philosophers();
	i = 0;
	while (i < ph_cnt)
	{	
		pthread_mutex_lock(phs[i]->forks_auth);
		i++;
	}
}

void	start_work_load(void)
{
	t_philo			**phs;
	int32_t			ph_cnt;

	ph_cnt = get_params()->num_philo;
	phs = get_philosophers();
	//prepare_queues(phs);
	while (true)
		work_loop(phs, ph_cnt);
}
