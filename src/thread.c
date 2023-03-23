/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 07:48:39 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_threads(void)
{
	pthread_t	*threads;
	int32_t		i;
	t_philo		**phs;

	phs = get_philosophers();
	i = 0;
	threads = malloc(get_params()->num_philo * sizeof(pthread_t));
	while (i < get_params()->num_philo)
	{
		pthread_create(&threads[i], NULL, philo_work, &phs[i]);
		phs[i]->thread_id = threads[i];
		i++;
	}
	get_data()->thread_ids = threads;
}

void	*detach_threads(void)
{
	int32_t		i;
	pthread_t	*threads;

	i = 0;
	threads = get_data()->thread_ids;
	while (i < get_params()->num_philo)
	{	
		pthread_detach(threads[i]);
		i++;
	}
}

void	*free_threads(void)
{
	free(get_data()->thread_ids);
}
