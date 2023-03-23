/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 08:31:53 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_forks(void)
{
	bool	*forks;
	int32_t	i;

	i = 0;
	forks = malloc(get_params()->num_philo * sizeof(bool));
	while (i < get_params()->num_philo)
	{
		forks[i] = false;
		i++;
	}
	get_data()->forks = forks;
	return ((void *)forks);
}

void	*free_forks(void)
{
	free(get_data()->forks);
}

void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	print_msg("%lu %i has taken a fork\n", ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	print_msg("%lu %i has taken a fork\n", ph);
	pthread_mutex_unlock(ph->right_fork);
}
