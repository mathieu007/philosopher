/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/24 15:45:30 by math             ###   ########.fr       */
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
		pthread_create(&threads[i], NULL, philo_work, phs[i]);
		phs[i]->thread_id = threads[i];
		// if (pthread_join(threads[i], NULL) == -1)
		// 	get_data()->exit_threads = true;
		i++;
	}
	return (NULL);
}

void	*free_threads(void)
{
	free(get_data()->thread_ids);
	return (NULL);
}
