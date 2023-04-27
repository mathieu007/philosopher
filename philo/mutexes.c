/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/27 12:21:29 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_print_buffer(void)
{
	t_print_buffer	*buffer;
	t_data			*data;
	size_t			size;

	size = 1000000;
	data = get_data();
	buffer = malloc(sizeof(t_print_buffer));
	if (buffer == NULL)
		return (NULL);
	buffer->read = malloc(sizeof(char) * size);
	buffer->write = malloc(sizeof(char) * size);
	if (!buffer->read || !buffer->write)
		return (NULL);
	buffer->count = 0;
	buffer->stop_print = false;
	buffer->stop_count = 0;
	pthread_mutex_lock(data->write);
	get_data()->buffer = buffer;
	pthread_mutex_unlock(data->write);
	return (buffer);
}

static void	*set_philo_mutexes(t_philo **phs, int32_t i,
	pthread_mutex_t *forks_mutexes, bool *forks)
{
	t_param	*params;

	params = get_params();
	pthread_mutex_init(&(forks_mutexes[i]), NULL);
	phs[i]->start_simulation = malloc(sizeof(pthread_mutex_t));
	if (!phs[i]->start_simulation)
		return (NULL);
	pthread_mutex_init(phs[i]->start_simulation, NULL);
	phs[i]->left_fork = &(forks_mutexes[i]);
	phs[i]->left_fork_taken = &forks[i];
	phs[prev_ph(i, params->num_philo)]->right_fork = &(forks_mutexes[i]);
	phs[prev_ph(i, params->num_philo)]->right_fork_taken = &forks[i];
	return (phs[i]->start_simulation);
}

void	*init_mutexes(void)
{
	int32_t				i;
	t_philo				**phs;
	t_data				*data;

	data = get_data();
	data->write = malloc(sizeof(pthread_mutex_t));
	data->forks = malloc(sizeof(pthread_mutex_t) * get_params()->num_philo);
	data->forks_taken = malloc(sizeof(pthread_mutex_t)
			* get_params()->num_philo);
	if (!data->write || !data->forks || !data->forks_taken)
		return (NULL);
	pthread_mutex_init(data->write, NULL);
	i = 0;
	phs = get_philosophers();
	while (i < get_params()->num_philo)
	{
		set_philo_mutexes(phs, i, data->forks, data->forks_taken);
		i++;
	}
	return (data->forks);
}

static void	free_philo_mutexes(t_philo **phs)
{
	int32_t		i;
	int32_t		count;

	count = get_params()->num_philo;
	i = 0;
	if (phs)
	{
		while (i < count)
		{
			if (phs[i]->start_simulation)
			{
				pthread_mutex_destroy(phs[i]->start_simulation);
				free(phs[i]->start_simulation);
				phs[i]->start_simulation = NULL;
			}
			if (phs[i]->left_fork)
			{
				pthread_mutex_destroy(phs[i]->left_fork);
				phs[i]->left_fork = NULL;
			}
			i++;
		}
	}
}

void	*free_mutexes(void)
{
	t_data		*data;

	data = get_data();
	if (data->write)
	{
		pthread_mutex_destroy(data->write);
		free(data->write);
		data->write = NULL;
	}	
	free_philo_mutexes(get_philosophers());
	if (data->forks)
		free(data->forks);
	data->forks = NULL;
	if (data->forks_taken)
		free(data->forks_taken);
	data->forks_taken = NULL;
	return (NULL);
}
