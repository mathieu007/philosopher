/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/04 10:18:34 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	set_philo(t_philo *ph, t_data *data, int32_t i)
{
	ph->params = get_params();
	ph->data = data;
	ph->position = i;
	ph->dispatched = false;
	ph->name = i + 1;
	ph->eat_count = 0;
	ph->last_meal = 0;
	ph->exit_status = 0;
	ph->start_simulation = NULL;
	ph->left_fork = NULL;
	ph->right_fork = NULL;
	ph->right_fork_taken = false;
	ph->left_fork_taken = false;
}

void	*init_philosophers(void)
{
	t_param	*params;
	int32_t	i;
	t_philo	**phs;
	t_data	*data;

	i = 0;
	data = get_data();
	params = get_params();
	phs = malloc(sizeof(t_philo *) * (params->num_philo));
	if (phs == NULL)
		return (NULL);
	while (i < params->num_philo)
	{
		phs[i] = malloc(sizeof(t_philo));
		if (phs[i] == NULL)
			return (NULL);
		set_philo(phs[i], data, i);
		i++;
	}
	data->philos = phs;
	return (phs);
}
