/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/22 11:40:25 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_param	*get_params(void)
{
	static t_param	params[0];

	return (&params[0]);
}

void	init_params(int32_t argc, char **argv)
{
	t_param	*params;

	params = get_params();
	params->num_philo = argv[1];
	params->time_to_die = argv[2];
	params->time_to_eat = argv[3];
	params->time_to_sleep = argv[4];
	if (argc == 6)
		params->eat_at_least = argv[5];
}
