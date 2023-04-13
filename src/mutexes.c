/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/12 21:09:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#ifdef __APPLE__

pthread_mutexattr_t	*get_mutex_attr(void)
{
	pthread_mutexattr_t	*attr;

	attr = malloc(sizeof(pthread_mutexattr_t));
	pthread_mutexattr_init(attr);
	pthread_mutexattr_settype(attr, PTHREAD_MUTEX_POLICY_FAIRSHARE_NP);
	return (attr);
}
#elif __linux

// pthread_mutexattr_t	*get_mutex_attr(void)
// {
// 	pthread_mutexattr_t	*attr;

// 	attr = malloc(sizeof(pthread_mutexattr_t));
// 	pthread_mutexattr_init(attr);
// 	pthread_mutexattr_settype(attr, NULL);
// 	return (attr);
// }
#elif __unix

#elif __posix

#endif

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
	pthread_mutex_init(data->write, NULL);
	i = 0;
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * params->num_philo);
	phs = get_philosophers();
	data->forks = forks_mutexes;
	while (i < params->num_philo)
	{
		phs[i]->auth_forks = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(&(forks_mutexes[i]), NULL);
		pthread_mutex_init(phs[i]->auth_forks, NULL);
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
