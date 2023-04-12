/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/11 21:00:22 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	main(int32_t argc, char **argv)
{
	t_philo	**phs;
	int32_t	ph_cnt;

	if (argc < 5 || argc > 6 || !try_init_params(argc, argv))
	{
		if (write(2, "error: invalid arguments.\n", 27) == -1)
			return (1);
		return (1);
	}
	if (get_params()->num_philo == 0 || get_params()->num_philo > 1000)
	{
		if (write(2, "error: invalid number of philosophers.\n", 40) == -1)
			return (1);
		return (1);
	}
	init_philosophers();
	if (get_params()->num_philo == 1)
	{
		printf("%i %i has taken a fork\n", 0, 1);
		usleep(get_params()->time_to_die * 1000);
		printf("%i %i died\n", get_params()->time_to_die, 1);
		exit(0);
	}
	init_mutexes();
	lock_all_philos();
	init_threads();
	ph_cnt = get_params()->num_philo;
	phs = get_philosophers();
	start_simulation(phs, ph_cnt);
	join_threads();
	return (0);
}
