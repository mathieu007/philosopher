/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/05 11:16:25 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
