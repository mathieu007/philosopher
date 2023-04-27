/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/27 09:41:21 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_threads(void)
{
	pthread_t	*threads;
	int32_t		i;
	t_philo		**phs;
	int32_t		num_philo;

	phs = get_philosophers();
	num_philo = get_params()->num_philo;
	threads = malloc(num_philo * sizeof(pthread_t));
	get_data()->thread_ids = threads;
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_even_work, phs[i]);
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	i = 1;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_odd_work, phs[i]);
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	usleep(100000);
	return (NULL);
}

void	wait_threads_ready(t_data *data, int32_t ph_cnt)
{
	while (true)
	{
		pthread_mutex_lock(data->write);
		if (data->threads_ready == ph_cnt)
		{
			pthread_mutex_unlock(data->write);
			break ;
		}
		pthread_mutex_unlock(data->write);
	}
}

void	*join_threads(void)
{
	pthread_t	*threads;
	int32_t		i;
	int32_t		num_philo;
	t_philo		**phs;
	void		*status;

	i = 0;
	status = NULL;
	phs = get_philosophers();
	num_philo = get_params()->num_philo;
	threads = get_data()->thread_ids;
	while (i < num_philo)
	{
		pthread_join(threads[i], status);
		i++;
	}
	pthread_mutex_lock(get_data()->write);
	get_data()->buffer->stop_print = true;
	pthread_mutex_unlock(get_data()->write);
	pthread_join(get_data()->buffer->thread_id, status);
	return (NULL);
}
