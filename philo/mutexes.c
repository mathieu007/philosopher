/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/21 08:44:53 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_print_buffer(void)
{
	t_print_buffer	*buffer;
	t_data			*data;
	size_t			size;

	size = 1000000;
	data = get_data();
	pthread_mutex_lock(data->write);
	buffer = malloc(sizeof(t_print_buffer));
	get_data()->buffer = buffer;
	buffer->capacity = size;
	buffer->read = malloc(sizeof(char) * size);
	buffer->write = malloc(sizeof(char) * size);
	buffer->count = 0;
	pthread_mutex_unlock(data->write);
}

void	init_mutexes(void)
{
	int32_t				i;
	t_philo				**phs;
	pthread_mutex_t		*forks_mutexes;
	t_data				*data;
	t_param				*params;

	data = get_data();
	params = get_params();
	data->write = malloc(sizeof(pthread_mutex_t));
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * params->num_philo);
	data->forks = forks_mutexes;
	pthread_mutex_init(data->write, NULL);
	i = 0;
	phs = get_philosophers();
	while (i < params->num_philo)
	{
		pthread_mutex_init(&(forks_mutexes[i]), NULL);
		phs[i]->start_simulation = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phs[i]->start_simulation, NULL);
		phs[i]->left_fork = &(forks_mutexes[i]);
		phs[prev_ph(i, params->num_philo)]->right_fork = &(forks_mutexes[i]);
		i++;
	}
}

static void	free_philo_mutex(t_philo *ph)
{
	if (ph != NULL)
	{	
		if (ph->start_simulation)
		{
			pthread_mutex_destroy(ph->start_simulation);
			free(ph->start_simulation);
			ph->start_simulation = NULL;
		}
		if (ph->left_fork)
		{
			pthread_mutex_destroy(ph->left_fork);
			ph->left_fork = NULL;
		}
	}
}

void	*free_mutexes(void)
{
	t_philo		**phs;
	t_data		*data;
	int32_t		i;
	int32_t		count;

	i = 0;
	data = get_data();
	phs = get_philosophers();
	if (data->write)
	{
		pthread_mutex_destroy(data->write);
		free(data->write);
		data->write = NULL;
	}	
	count = get_params()->num_philo;
	while (i < count)
	{
		free_philo_mutex(phs[i]);
		i++;
	}
	if (data->forks)
		free(data->forks);
	data->forks = NULL;
	return (NULL);
}
