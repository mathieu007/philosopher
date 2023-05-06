/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/06 09:09:33 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	hard_code_1philo(void)
{
	printf("%i %i has taken a fork\n", 0, 1);
	usleep(get_params()->time_to_die);
	printf("%i %i died\n", (int32_t)(get_params()->time_to_die / 1000), 1);
	return (0);
}

// int32_t	hard_code_philo_eat_gr(void)
// {
// 	printf("%i %i has taken a fork\n", 0, 1);
// 	printf("%i %i has taken a fork\n", 0, 1);
// 	printf("%i %i is eating\n", 0, 1);
// 	usleep(get_params()->time_to_die * 1000);
// 	printf("%i %i died\n", get_params()->time_to_die, 1);
// 	return (0);
// }

// int32_t	hard_code_philo_eat_slp_gr(void)
// {
// 	printf("%i %i has taken a fork\n", 0, 1);
// 	printf("%i %i has taken a fork\n", 0, 1);
// 	printf("%i %i is eating\n", 0, 1);
// 	usleep(get_params()->time_to_eat * 1000);
// 	printf("%i %i is sleeping\n", get_params()->time_to_eat, 1);
// 	usleep(get_params()->time_to_die - get_params()->time_to_eat);
// 	printf("%i %i died\n", get_params()->time_to_die, 1);
// 	return (0);
// }

int32_t	error_msg(const char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
		return (1);
	return (1);
}

int32_t	handle_parse_n_error(int32_t argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("error: invalid number of arguments.\n"));
	if (!try_init_params(argc, argv))
		return (error_msg("error: invalid type of arguments.\n"));
	else if (get_params()->num_philo == 0 || get_params()->num_philo > 3000)
		return (error_msg("error: invalid number of philosophers.\n"));
	else if (get_params()->time_to_eat < 60000)
		return (error_msg("error: time to eat parameter is invalid.\n"));
	else if (get_params()->time_to_sleep < 60000)
		return (error_msg("error: time to sleep parameter is invalid.\n"));
	return (0);
}
