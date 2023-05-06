/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/06 09:02:37 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	*set_philo_odd_thread_id(int32_t i, t_philo **phs)
{
	if (pthread_create(&get_data()->thread_ids[i], NULL, philo_odd_work,
			phs[i]) != 0)
		return (NULL);
	phs[i]->thread_id = get_data()->thread_ids[i];
	return (phs);
}

static void	*set_philo_even_thread_id(int32_t i, t_philo **phs)
{
	if (pthread_create(&get_data()->thread_ids[i], NULL, philo_even_work,
			phs[i]) != 0)
		return (NULL);
	phs[i]->thread_id = get_data()->thread_ids[i];
	return (phs);
}

void	*init_threads(void)
{
	int32_t		i;
	t_philo		**phs;

	phs = get_philosophers();
	get_data()->thread_ids = malloc(get_params()->num_philo
		* sizeof(pthread_t));
	if (get_data()->thread_ids == NULL)
		return (NULL);
	i = 0;
	while (i < get_params()->num_philo)
	{
		set_philo_odd_thread_id(i, phs);
		i += 2;
	}
	i = 1;
	while (i < get_params()->num_philo)
	{
		set_philo_even_thread_id(i, phs);
		i += 2;
	}
	usleep(100000);
	return (get_data()->thread_ids);
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
	void		*status;

	i = 0;
	status = NULL;
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
