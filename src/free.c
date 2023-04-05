/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 15:07:11 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_philos()
{
	t_philo	**phs;
	int32_t i;
	
	phs = get_philosophers();
	i = 0;
	while (i < get_params()->num_philo)
	{
		free(phs[i]);
		i++;		
	}
	free(phs);
	return (NULL);
}

void	*free_threads(void)
{
	t_philo	**phs;
	int32_t	i;

	phs = get_philosophers();
	i = 0;
	while (i < get_params()->num_philo)
	{
		pthread_detach(phs[i]->thread_id);
		i++;
	}
	free(get_data()->thread_ids);
	return (NULL);
}

void	*free_all(void)
{
	free_threads();
	free_fifo(get_data()->odd_queue);
	free_fifo(get_data()->even_queue);	
	free_mutexes();
	free_philos();
	free(get_data());
	free(get_params());	
	return (NULL);
}	
