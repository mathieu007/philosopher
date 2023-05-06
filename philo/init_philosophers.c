/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/06 16:04:57 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	set_philo(t_philo *ph, t_data *data, int32_t i)
{
	ph->params = get_params();
	ph->data = data;
	ph->position = i;
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

static void	init_dispatch_order(void)
{
	t_param	*params;
	int32_t	i;
	int32_t	*dispatch_order;
	t_data	*data;
	int32_t	max;

	i = 0;
	data = get_data();
	params = get_params();
	dispatch_order = malloc(sizeof(int32_t *) * (params->num_philo));
	if (dispatch_order == NULL)
		return (NULL);
	if (params->num_philo % 2 == 1)
	{
		max = params->num_philo - 1;
		dispatch_order[params->num_philo - 1] = params->num_philo;	
	}
	else
		max = params->num_philo;
	while (i < max)
	{
		dispatch_order[i] = i + 1;
		i += 2;
	}
	i = 1;
	while (i < max)
	{
		dispatch_order[i] = i + 1;
		i += 2;
	}
	data->last_philo_index_in_queue = 0;
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
	init_dispatch_order();
	return (phs);
}
