/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 11:05:34 by mroy             ###   ########.fr       */
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
		usleep(1);
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

void	process_even_philos(t_philo **phs, int32_t ph_cnt)
{
	t_philo			*ph;
	int32_t 		i;
	static int32_t	time_to_eat;
	static int32_t	time_to_think;
	static int32_t	count;

	if (time_to_eat == 0)
	{
		time_to_eat = get_params()->time_to_eat * 1000;
		time_to_think = get_params()->time_to_think * 1000;
	}		
	i = 0;
	while (i < ph_cnt)
	{	
		ph = phs[i];
		authorize_forks_take(ph, phs, ph_cnt);
		i += 2;
	}
	usleep(time_to_eat - time_to_think);
	process_odd_philos(phs, ph_cnt);
}

void	process_odd_philos(t_philo **phs, int32_t ph_cnt)
{
	t_philo	*ph;
	// int32_t	diff;
	int32_t i;

	i = 1;
	while (i < ph_cnt)
	{	
		ph = phs[i];
		if (ph == NULL)
		{
			usleep(10);
			continue ;
		}
		authorize_forks_take(ph, phs, ph_cnt);
		i += 2;
	}
	// diff = get_relative_time_mc() - diff;
	usleep(get_params()->time_to_eat * 1000 - 10000);
	process_even_philos(phs, ph_cnt);
}

static void	work_loop(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	t_fifo		*odd_fifo;
	t_fifo		*even_fifo;
	// uint32_t	base_time;

	i = 0;
	
	
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
	t_philo		**phs;
	int32_t		ph_cnt;

	ph_cnt = get_params()->num_philo;
	phs = get_philosophers();
	
	process_odd_philos(phs, ph_cnt);
}
