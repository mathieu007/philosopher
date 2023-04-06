/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 06:49:48 by math             ###   ########.fr       */
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

bool	try_init_params(int32_t argc, char **argv)
{
	t_param	*params;

	params = malloc(sizeof(t_param));
	if (!is_valid(argv[1]) || !is_valid(argv[2]) || !is_valid(argv[3])
		|| !is_valid(argv[4]))
		return (false);
	params->num_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->time_to_think = params->time_to_die - params->time_to_sleep - params->time_to_eat
		- params->time_to_eat;
	if (argc == 6)
	{
		if (!is_valid(argv[5]))
			return (false);
		params->must_eat = ft_atoi(argv[5]);
	}
	else
		params->must_eat = INT32_MAX;
	get_data()->params = params;
	return (true);
}
