/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/20 11:25:07 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	hard_code_1philo(void)
{
	printf("%i %i has taken a fork\n", 0, 1);
	usleep(get_params()->time_to_die * 1000);
	printf("%i %i died\n", get_params()->time_to_die, 1);
	exit(0);
}

static void	error_msg(const char *msg)
{
	if (write(2, msg, ft_strlen(msg)) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}

static void	handle_parse_n_error(int32_t argc, char **argv)
{
	if (argc < 5 || argc > 6 || !try_init_params(argc, argv))
		error_msg("error: invalid arguments.\n");
	else if (get_params()->num_philo == 0 || get_params()->num_philo > 5000)
		error_msg("error: invalid number of philosophers.\n");
	else if (get_params()->time_to_eat < 60)
		error_msg("error: time to eat parameter is invalid.\n");
	else if (get_params()->time_to_sleep < 60)
		error_msg("error: time to sleep parameter is invalid.\n");
}

int32_t	main(int32_t argc, char **argv)
{
	handle_parse_n_error(argc, argv);
	init_philosophers();
	if (get_params()->num_philo == 1)
		hard_code_1philo();
	init_mutexes();
	init_print_buffer();
	lock_all_philos();
	init_threads();
	start_simulation();
	join_threads();
	free_all();
	return (0);
}
