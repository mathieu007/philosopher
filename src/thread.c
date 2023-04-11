/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/11 08:15:21 by mroy             ###   ########.fr       */
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
	return (NULL);
}

void	*detach_all_philos(void)
{
	t_philo		**phs;
	int32_t		i;
	int32_t		num_philo;

	i = 0;
	phs = get_philosophers();
	num_philo = get_params()->num_philo;
	while (i < num_philo)
	{
		pthread_detach(phs[i]->thread_id);
		free_philo(phs[i]);
		i++;
	}
	return (NULL);
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
		if (pthread_join(threads[i], &status) != 0 || *((int32_t *)status) == 1)
		{
			detach_all_philos();
			free_all();
			exit(1);
		}
		i++;
	}
	free_all();
	return (NULL);
}
