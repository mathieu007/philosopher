/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 17:26:20 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	authorize_forks_take(t_philo *ph, t_philo **phs, int32_t ph_cnt)
{
	t_philo	*ph_prev;
	t_philo	*ph_next;

	ph_prev = phs[prev_ph(ph->position, ph_cnt)];
	ph_next = phs[next_ph(ph->position, ph_cnt)];
	while (ph_prev->forks_taken || ph_next->forks_taken)
		usleep(100);
	pthread_mutex_unlock(ph->forks_auth);
	usleep(100);
	pthread_mutex_lock(ph->forks_auth);
}

void	process_even_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	int32_t			count;
	static t_fifo	*even_fifo;
	static int32_t	time_to_eat;
	static int32_t	time_to_think;

	if (time_to_eat == 0)
	{
		time_to_eat = get_params()->time_to_eat * 1000;
		time_to_think = get_params()->time_to_think * 1000;
		even_fifo = get_data()->even_queue;
	}
	count = get_data()->even_count;
	while (count > 0 && !should_exit())
	{	
		ph = fifo_concurent_get(even_fifo);
		if (ph == NULL)
		{
			usleep(1000);
			continue ;
		}
		if (ph->eat_count == get_params()->must_eat)
		{
			get_data()->odd_count--;
			fifo_concurrent_pop(even_fifo);
		}
		authorize_forks_take(ph, phs, ph_cnt);
		fifo_concurrent_pop(even_fifo);
		count--;
	}
	if (should_exit())
		return ;
	process_odd_wait_list(phs, ph_cnt);
}

void	process_odd_wait_list(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	int32_t			count;
	static t_fifo	*odd_fifo;
	static int32_t	time_to_eat;
	static int32_t	time_to_think;

	if (time_to_eat == 0)
	{
		time_to_eat = get_params()->time_to_eat * 1000;
		time_to_think = get_params()->time_to_think * 1000;
		odd_fifo = get_data()->odd_queue;
	}
	count = get_data()->odd_count;
	while (count > 0 && !should_exit())
	{	
		ph = fifo_get(odd_fifo);			
		if (ph == NULL)
		{
			usleep(1000);
			continue ;
		}
		if (ph->eat_count == get_params()->must_eat)
		{
			get_data()->odd_count--;
			fifo_concurrent_pop(odd_fifo);
		}
		authorize_forks_take(ph, phs, ph_cnt);
		fifo_concurrent_pop(odd_fifo);
		count--;
	}
	if (should_exit())
		return ;
	process_even_wait_list(phs, ph_cnt);
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
	t_philo					**phs;
	int32_t					ph_cnt;
	static __thread t_data	*data;	

	data = get_data();
	ph_cnt = get_params()->num_philo;
	phs = get_philosophers();
	process_odd_wait_list(phs, ph_cnt);
	free_all();
	exit(0);
}
