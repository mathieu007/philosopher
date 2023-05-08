/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/08 14:20:20 by mroy             ###   ########.fr       */
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

static void	init_dispatch_order(t_philo **phs)
{
	t_param	*params;
	int32_t	i;
	t_data	*data;
	int32_t	max;

	i = 0;
	data = get_data();
	params = get_params();
	if (params->num_philo % 2 == 1)
		max = params->num_philo - 1;
	else
		max = params->num_philo;
	while (i < max)
	{
		fifo_add(data->queue, phs[i]);
		i += 2;
	}
	i = 1;
	while (i < max)
	{
		fifo_add(data->queue, phs[i]);
		i += 2;
	}
	if (params->num_philo % 2 == 1)
		fifo_add(data->queue, phs[params->num_philo - 1]);
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
	data->queue = fifo_new(params->num_philo);	
	while (i < params->num_philo)
	{
		phs[i] = malloc(sizeof(t_philo));		
		if (phs[i] == NULL)
			return (NULL);
		set_philo(phs[i], data, i);	
		i++;
	}
	data->philos = phs;
	init_dispatch_order(phs);
	return (phs);
}
