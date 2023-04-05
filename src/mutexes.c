/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 07:05:00 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

pthread_mutexattr_t	get_mutex_attr(int32_t type)
{
	pthread_mutexattr_t	attr;

	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, type);
	// pthread_mutexattr_setprotocol(&attr, protocol);
	return (attr);
}

void	init_mutexes(void)
{
	int32_t				i;
	t_philo				**phs;
	pthread_mutex_t		*forks_mutexes;
	t_data				*data;
	// pthread_mutexattr_t	attr;

	data = get_data();
	data->meal_authorization = malloc(sizeof(pthread_mutex_t));
	data->write = malloc(sizeof(pthread_mutex_t));
	// attr = get_mutex_attr((int32_t)PTHREAD_MUTEX_TIMED_NP);
	pthread_mutex_init(data->meal_authorization, NULL);
	pthread_mutex_init(data->write, NULL);
	i = 0;
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * get_params()->num_philo);
	data->odd_queue = new_fifo(get_params()->num_philo / 2);
	data->even_queue = new_fifo(get_params()->num_philo / 2);
	phs = get_philosophers();
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
