/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/27 11:10:55 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int32_t	hard_code_1philo(void)
{
	printf("%i %i has taken a fork\n", 0, 1);
	usleep(get_params()->time_to_die * 1000);
	printf("%i %i died\n", get_params()->time_to_die, 1);
	return (0);
}

static int32_t	error_msg(const char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
		return (1);
	return (1);
}

static int32_t	handle_parse_n_error(int32_t argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_msg("error: invalid number of arguments.\n"));
	if (!try_init_params(argc, argv))
		return (error_msg("error: invalid type of arguments.\n"));
	else if (get_params()->num_philo == 0 || get_params()->num_philo > 3000)
		return (error_msg("error: invalid number of philosophers.\n"));
	else if (get_params()->time_to_eat < 60)
		return (error_msg("error: time to eat parameter is invalid.\n"));
	else if (get_params()->time_to_sleep < 60)
		return (error_msg("error: time to sleep parameter is invalid.\n"));
	return (0);
}

int32_t	main(int32_t argc, char **argv)
{
	if (handle_parse_n_error(argc, argv) == 1)
		return (free_all(), 1);
	if (!init_philosophers())
		return (free_all(), error_msg("Error: cannot init philosophers."));
	if (get_params()->num_philo == 1)
		return (hard_code_1philo(), free_all(), 0);
	if (!init_mutexes())
		return (free_all(), error_msg("Error: cannot init mutexes."));
	if (!init_print_buffer())
		return (free_all(), error_msg("Error: cannot init buffer."));
	lock_all_philos();
	if (!init_threads())
		return (free_all(), error_msg("Error: cannot init threads."));
	if (!start_simulation())
		return (free_all(), error_msg("Error: cannot start simulation."));
	join_threads();
	return (free_all(), 0);
}
