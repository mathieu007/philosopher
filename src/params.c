/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 13:22:09 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_param	*get_params(void)
{
	static t_param	params[0];

	return (&params[0]);
}

void	init_params(int32_t argc, char **argv, int32_t min_sleep_time)
{
	t_param	*params;

	params = get_params();
	params->num_philo = argv[1];
	params->time_to_die = argv[2];
	params->time_to_eat = argv[3];
	params->time_to_sleep = argv[4];
	if (argc == 6)
		params->eat_at_least = argv[5];
	params->min_sleep_time = min_sleep_time;
}
