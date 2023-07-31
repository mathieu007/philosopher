/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/07/30 21:08:15 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_param	*get_params(void)
{
	return (get_data()->params);
}

bool	is_valid(char *str)
{
	int		len;
	char	*str_start;

	if (str == NULL)
		return (false);
	len = ft_strlen(str);
	if (len == 0)
		return (false);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str && *str == '+')
		str++;
	str_start = str;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if ((str_start != str) && (str[-1] < '0' || str[-1] > '9'))
		return (false);
	if (*str - *str_start > 12)
		return (false);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '\0')
		return (true);
	return (false);
}

void	set_time_to_think(t_param	*params)
{
	if (is_odd(params->num_philo))
	{
		if (params->time_to_eat * 3 < params->time_to_die)
			set_constant(params->time_to_die - params->time_to_eat * 3,
				&(params->time_to_think));
		else
			set_constant(0, &(params->time_to_think));
	}
	else if (!is_odd(params->num_philo))
	{
		if (params->time_to_eat * 2 < params->time_to_die)
			set_constant(params->time_to_die - params->time_to_eat * 2,
				&(params->time_to_think));
		else
			set_constant(0, &(params->time_to_think));
	}
}

bool	try_init_params(int32_t argc, char **argv)
{
	static t_param	params;

	get_data()->params = &params;
	if (!is_valid(argv[1]) || !is_valid(argv[2]) || !is_valid(argv[3])
		|| !is_valid(argv[4]))
		return (false);
	set_constant(ft_atoi(argv[1]), &(params.num_philo));
	set_constant(ft_atoi(argv[2]), &(params.time_to_die));
	set_constant(ft_atoi(argv[3]), &(params.time_to_eat));
	set_constant(ft_atoi(argv[4]), &(params.time_to_sleep));
	set_time_to_think(&params);
	set_constant((params.time_to_die * 1000)
		- ((params.time_to_think * 1000) / 2),
		&(params.time_cycle));
	if (argc == 6)
	{
		if (!is_valid(argv[5]))
			return (false);
		set_constant(ft_atoi(argv[5]), &(params.must_eat));
	}
	else
		set_constant(INT32_MAX, &(params.must_eat));
	return (true);
}
