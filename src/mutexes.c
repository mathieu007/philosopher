/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 08:31:13 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_mutexes(void)
{
	int32_t			i;
	t_philo			**phs;
	pthread_mutex_t	*forks_mutexes;
	int32_t			ph_cnt;

	pthread_mutex_init(get_data()->forks_authorization, NULL);
	pthread_mutex_init(get_data()->meal_authorization, NULL);
	pthread_mutex_init(get_data()->write, NULL);
	i = 0;
	forks_mutexes = malloc(sizeof(pthread_mutex_t) * get_params()->num_philo);
	ph_cnt = get_params()->num_philo;
	while (i < get_params()->num_philo)
	{
		pthread_mutex_init(&forks_mutexes[i], NULL);
		phs[i]->left_fork = &forks_mutexes[i];
		phs[prev_ph(i, ph_cnt)]->right_fork = &forks_mutexes[i];
		i++;
	}
}
