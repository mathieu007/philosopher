/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 07:09:25 by math             ###   ########.fr       */
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
	i = 0;
	num_philo = get_params()->num_philo;
	threads = malloc(num_philo * sizeof(pthread_t));
	get_data()->thread_ids = threads;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_work_even, phs[i]);
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	i = 1;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_work_odd, phs[i]);
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	return (NULL);
}

t_philo	**get_thread_philo(void)
{
	static t_philo	*ph;

	return (&ph);
}

void	*free_threads(void)
{
	free(get_data()->thread_ids);
	return (NULL);
}
