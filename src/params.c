/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/18 15:08:25 by math             ###   ########.fr       */
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


void	set_constant_char(const char val, const char *addr)
{
	*((char *)addr) = val;
}

void	set_constant(const int32_t val, const int32_t *addr)
{
	*((int32_t *)addr) = val;
}

void	set_constant64(const int64_t val, const int64_t *addr)
{
	*((int64_t *)addr) = val;
}


/// @brief [17.6.5.9/3] A C++ standard library function shall not 
/// directly or indirectly modify objects (1.10) accessible by threads 
/// other than the current thread unless the objects are accessed directly 
/// or indirectly via the function’s non-const arguments, including this.
/// @param argc 
/// @param argv 
/// @return 
bool	try_init_params(int32_t argc, char **argv)
{
	t_param	*params;

	params = malloc(sizeof(t_param));
	if (!is_valid(argv[1]) || !is_valid(argv[2]) || !is_valid(argv[3])
		|| !is_valid(argv[4]))
		return (false);
	set_constant(ft_atoi(argv[1]), &(params->num_philo));
	set_constant(ft_atoi(argv[2]), &(params->time_to_die));
	set_constant(ft_atoi(argv[3]), &(params->time_to_eat));
	set_constant(ft_atoi(argv[4]), &(params->time_to_sleep));
	set_constant(params->time_to_die - params->time_to_sleep
		- params->time_to_eat, &(params->time_to_think));
	set_constant(((params->time_to_think / 2) + params->time_to_eat
			+ params->time_to_sleep) * 1000, &(params->time_cycle));
	if (argc == 6)
	{
		if (!is_valid(argv[5]))
			return (false);
		set_constant(ft_atoi(argv[5]), &(params->must_eat));
	}
	else
		set_constant(INT32_MAX, &(params->must_eat));
	get_data()->params = params;
	return (true);
}
