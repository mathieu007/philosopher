/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 17:34:01 by mroy             ###   ########.fr       */
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

pthread_mutexattr_t	*get_mutex_attr(void)
{
	pthread_mutexattr_t	*attr;

	attr = malloc(sizeof(pthread_mutexattr_t));
	pthread_mutexattr_init(attr);
	pthread_mutexattr_settype(attr, PTHREAD_MUTEX_TIMED_NP);
	return (attr);
}
#elif __unix

#elif __posix

#endif

static void	add_even_queue(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		ri;
	t_fifo		*even_fifo;
	int32_t		count;

	i = 0;
	if (ph_cnt % 2 == 0)
	{
		ri = ph_cnt - 2;
		count = (ph_cnt / 2) - 1;
	}		
	else
	{
		ri = ph_cnt - 1;
		count = (ph_cnt / 2);
	}
	even_fifo = get_data()->even_queue;
	while (i <= count)
	{
		fifo_put(even_fifo, (void *)phs[i]);
		if (i != ri)
			fifo_put(even_fifo, (void *)phs[ri]);
		i += 2;
		ri -= 2;
	}
}

static void	add_odd_queue(t_philo **phs, int32_t ph_cnt)
{
	int32_t		i;
	int32_t		ri;
	t_fifo		*odd_fifo;
	int32_t		count;

	i = 1;
	if (ph_cnt % 2 == 0)
	{
		ri = ph_cnt - 1;
		count = (ph_cnt / 2);
	}		
	else
	{
		ri = ph_cnt - 2;
		count = (ph_cnt / 2) - 1;
	}
	odd_fifo = get_data()->odd_queue;
	while (i <= ph_cnt / 2)
	{
		fifo_put(odd_fifo, (void *)phs[i]);
		if (i != ri)
			fifo_put(odd_fifo, (void *)phs[ri]);
		i += 2;
		ri -= 2;
	}
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
	data->meal_authorization = malloc(sizeof(pthread_mutex_t));
	data->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->meal_authorization, NULL);
	pthread_mutex_init(data->write, NULL);
	i = 0;
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * params->num_philo);
	data->odd_queue = new_fifo(1 + params->num_philo / 2);
	data->even_queue = new_fifo(1 + params->num_philo / 2);
	phs = get_philosophers();
	data->forks = forks_mutexes;
	while (i < params->num_philo)
	{
		phs[i]->forks_auth = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(phs[i]->forks_auth, NULL);
		pthread_mutex_init(&forks_mutexes[i], NULL);
		phs[i]->left_fork = &forks_mutexes[i];
		phs[prev_ph(i, params->num_philo)]->right_fork
			= &forks_mutexes[i];
		i++;
	}
	add_even_queue(phs, params->num_philo);
	add_odd_queue(phs, params->num_philo);
	pthread_mutex_lock(data->even_queue->_lock);
	data->even_count = data->even_queue->_count;
	pthread_mutex_unlock(data->even_queue->_lock);
	pthread_mutex_lock(data->odd_queue->_lock);
	data->odd_count = data->odd_queue->_count;
	pthread_mutex_unlock(data->odd_queue->_lock);
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
		pthread_mutex_destroy(phs[i]->left_fork);
		free(phs[i]->forks_auth);
		i++;
	}
	free(data->forks);
	return (NULL);
}
