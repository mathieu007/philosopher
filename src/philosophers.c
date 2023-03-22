/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/21 20:27:57 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_philo	**get_philosophers()
{
	static t_philo	**philos;

	return (&philos[0]);
}

void	*init_philosophers(void)
{
	t_param	*params;
	t_philo	**philos;
	int32_t	i;

	params = get_params();
	i = 0;
	philos = get_philosophers();
	while (i < params->num_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		i++;
	}
	return ((void *)philos);
}

void	philo_work(void *philo)
{
	t_philo			*ph;
	pthread_mutex_t	*authorized;

	authorized = get_data()->authorization;
	ph = (t_philo *) philo;
	while (true)
	{
		pthread_mutex_lock(authorized);
		if (!ph->is_authorized)
		{
			pthread_mutex_unlock(authorized);
			continue ;
		}
		take_forks(ph);
		ph->is_authorized = false;
		pthread_mutex_unlock(authorized);
	}
}
