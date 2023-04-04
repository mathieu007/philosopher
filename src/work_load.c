/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/04 16:49:39 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	authorize_forks_take(t_philo *ph, t_philo **phs,
	t_fifo *fifo, int32_t ph_cnt)
{
	t_philo	*ph_prev;
	t_philo	*ph_next;

	ph_prev = phs[prev_ph(ph->position, ph_cnt)];
	ph_next = phs[next_ph(ph->position, ph_cnt)];
	while (ph_prev->forks_taken && ph_next->forks_taken)
		usleep(1);
	fifo_concurrent_pop(fifo);
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

void	process_even_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo		*ph;
	int32_t		count;
	t_fifo		*even_fifo;

	even_fifo = get_data()->even_queue;
	count = get_data()->even_count;
	while (count > 0)
	{	
		ph = fifo_concurent_get(even_fifo);
		if (ph == NULL)
		{
			usleep(100);
			continue ;
		}
		count--;
		authorize_forks_take(ph, phs, even_fifo, ph_cnt);
	}
	usleep(get_params()->time_to_eat * 1000 - 10000);
	process_odd_wait_list(phs, ph_cnt);
}

void	process_odd_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo	*ph;
	int32_t	count;
	t_fifo	*odd_fifo;

	odd_fifo = get_data()->odd_queue;
	count = get_data()->odd_count;
	while (count > 0)
	{	
		ph = fifo_concurent_get(odd_fifo);
		if (ph == NULL)
		{
			usleep(100);
			continue ;
		}
		count--;
		authorize_forks_take(ph, phs, odd_fifo, ph_cnt);
	}
	usleep(get_params()->time_to_eat * 1000 - 10000);
	process_even_wait_list(phs, ph_cnt);
}

static void	work_loop(t_philo **phs, int32_t ph_cnt)
{
	int32_t	i;
	t_fifo	*odd_fifo;
	t_fifo	*even_fifo;

	i = 0;
	odd_fifo = get_data()->odd_queue;
	even_fifo = get_data()->even_queue;
	while (i < ph_cnt)
	{
		fifo_put(odd_fifo, (void *)phs[i]);
		i += 2;
	}
	i = 1;
	while (i < ph_cnt)
	{
		fifo_put(even_fifo, (void *)phs[i]);
		i += 2;
	}
	get_data()->even_count = even_fifo->_count;
	get_data()->odd_count = odd_fifo->_count;
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
	work_loop(phs, ph_cnt);
}
