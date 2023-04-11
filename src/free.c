/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/10 12:47:02 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


void	*free_philo(t_philo	*ph)
{
	free(ph->start_simulation);
	free(ph);
	return (NULL);
}

void	*free_philos(void)
{
	t_philo	**phs;
	int32_t	i;

	phs = get_philosophers();
	i = 0;
	while (i < get_params()->num_philo)
	{
		free_philo(phs[i]);
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
	//free_threads();
	free_mutexes();
	free_philos();
	free(get_params());
	return (NULL);
}	
