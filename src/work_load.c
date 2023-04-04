/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/04 07:08:37 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	authorize_forks_take(t_philo *ph)
{
	pthread_mutex_unlock(ph->forks_auth);
	usleep(1);
	pthread_mutex_lock(ph->forks_auth);
}

inline static void	work_sleep(int32_t wait_time)
{
	if (wait_time < 0)
		return ;
	usleep(wait_time);
}

void	process_even_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	int32_t			count;
	static t_fifo	*even_fifo;

	if (even_fifo == NULL)
		even_fifo = get_data()->even_queue;
	count = get_params()->num_philo / 2;
	while (count != 0)
	{	
		ph = fifo_concurent_get_pop(even_fifo);
		if (ph == NULL)
		{
			usleep(10);
			continue ;
		}
		authorize_forks_take(ph);
		count--;
	}
	// usleep(get_params()->time_to_eat * 1000 - 10000);
	process_odd_wait_list(phs, ph_cnt);
}

void	process_odd_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	int32_t			count;
	static t_fifo	*odd_fifo;

	if (odd_fifo == NULL)
		odd_fifo = get_data()->odd_queue;
	count = get_params()->num_philo / 2;
	while (count != 0)
	{	
		ph = fifo_concurent_get_pop(odd_fifo);
		if (ph == NULL)
		{
			usleep(10);
			continue ;
		}
		authorize_forks_take(ph);
		count--;
	}
	// usleep(get_params()->time_to_eat * 1000 - 10000);
	process_even_wait_list(phs, ph_cnt);
}

static void	work_loop(t_philo **phs, int32_t ph_cnt)
{
	int32_t	li;
	t_fifo	*odd_fifo;
	t_fifo	*even_fifo;

	li = 0;
	odd_fifo = get_data()->odd_queue;
	even_fifo = get_data()->even_queue;
	while (li < ph_cnt)
	{
		fifo_put(odd_fifo, (void *)phs[li]);
		li += 2;
	}
	li = 1;
	while (li < ph_cnt)
	{
		fifo_put(even_fifo, (void *)phs[li]);
		li += 2;
	}
	process_odd_wait_list(phs, ph_cnt);
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
