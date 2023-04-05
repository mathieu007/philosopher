/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 15:08:22 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_mutexes(void)
{
	int32_t				i;
	t_philo				**phs;
	pthread_mutex_t		*forks_mutexes;
	t_data				*data;

	data = get_data();
	data->meal_authorization = malloc(sizeof(pthread_mutex_t));
	data->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->meal_authorization, NULL);
	pthread_mutex_init(data->write, NULL);
	i = 0;
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * get_params()->num_philo);
	data->odd_queue = new_fifo(1 + get_params()->num_philo / 2);
	data->even_queue = new_fifo(1 + get_params()->num_philo / 2);
	phs = get_philosophers();
	data->forks = forks_mutexes;
	while (i < get_params()->num_philo)
	{
		phs[i]->forks_auth = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phs[i]->forks_auth, NULL);
		pthread_mutex_init(&forks_mutexes[i], NULL);
		phs[i]->left_fork = &forks_mutexes[i];
		phs[prev_ph(i, get_params()->num_philo)]->right_fork = &forks_mutexes[i];
		i++;
	}
}

void	*free_mutexes(void)
{
	t_philo		**phs;
	t_data		*data;
	int32_t		i;

	i = 0;
	data = get_data();
	phs = get_philosophers();
	pthread_mutex_destroy(data->meal_authorization);
	pthread_mutex_destroy(data->write);
	pthread_mutex_destroy(data->forks);
	free(data->meal_authorization);
	free(data->write);
	while (i < get_params()->num_philo)
	{
		pthread_mutex_destroy(phs[i]->forks_auth);
		free(phs[i]->forks_auth);
		i++;
	}
	free(data->forks);
	return (NULL);
}