/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/28 12:54:30 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	main(int32_t argc, char **argv)
{
	if (argc < 5 || argc > 6 || !try_init_params(argc, argv))
	{
		if (write(2, "error: invalid arguments.", 26) == -1)
			return (1);
		return (1);	
	}
	init_philosophers();
	init_mutexes();
	lock_all_philos();
	init_threads();
	start_work_load();
}
