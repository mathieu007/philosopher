/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/19 15:18:32 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*free_philo(t_philo	*ph, int32_t i)
{
	if (ph != NULL)
	{
		if (ph->start_simulation)
			free(ph->start_simulation);
		free(ph);
		get_data()->philos[i] = NULL;
	}
	return (NULL);
}

void	*free_philos(void)
{
	t_philo	**phs;
	int32_t	i;

	phs = get_philosophers();
	i = 0;
	if (phs)
	{
		while (i < get_params()->num_philo)
		{
			free_philo(phs[i], i);
			i++;
		}
		free(phs);
		if (get_data()->philos)
			get_data()->philos = NULL;
	}	
	return (NULL);
}

void	*free_threads(void)
{
	t_philo	**phs;
	int32_t	i;

	phs = get_philosophers();
	i = 0;
	if (phs)
	{
		while (i < get_params()->num_philo)
		{
			if (phs[i] != NULL)
				pthread_detach(phs[i]->thread_id);
			i++;
		}
		if (get_data()->thread_ids)
			free(get_data()->thread_ids);
		get_data()->thread_ids = NULL;
	}	
	return (NULL);
}

void	*free_all(void)
{
	free_mutexes();
	free_philos();
	free(get_data()->thread_ids);
	free(get_data()->buffer);
	free(get_params());
	return (NULL);
}	
