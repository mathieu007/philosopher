/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 20:17:20 by math             ###   ########.fr       */
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
