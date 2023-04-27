/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/27 10:22:38 by mroy             ###   ########.fr       */
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
			phs[i] = NULL;
			i++;
		}
		free(phs);
		if (get_data()->philos)
			get_data()->philos = NULL;
	}
	return (NULL);
}

void	free_buffer(void)
{
	if (get_data()->buffer != NULL)
	{
		free(get_data()->buffer->read);
		free(get_data()->buffer->write);
		free(get_data()->buffer);
	}
}

void	*free_all(void)
{
	free_mutexes();
	free_philos();
	if (get_data()->thread_ids != NULL)
		free(get_data()->thread_ids);
	if (get_data()->buffer != NULL)
		free_buffer();
	return (NULL);
}	
