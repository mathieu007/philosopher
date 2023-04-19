/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/18 20:46:30 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_print_buffer(void)
{
	t_print_buffer	*buffer;

	buffer = malloc(sizeof(t_print_buffer));
	get_data()->buffer = buffer;
	set_constant(100000, &(buffer->len));
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
		phs[i]->rw_lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phs[i]->start_simulation, NULL);
		pthread_mutex_init(phs[i]->rw_lock, NULL);
		phs[i]->left_fork = &(forks_mutexes[i]);
		phs[prev_ph(i, params->num_philo)]->right_fork = &(forks_mutexes[i]);
		i++;
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
	pthread_mutex_destroy(data->write);
	free(data->write);
	count = get_params()->num_philo;
	while (i < count)
	{
		pthread_mutex_destroy(phs[i]->left_fork);
		i++;
	}
	free(data->forks);
	return (NULL);
}
