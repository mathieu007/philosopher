/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/20 21:16:08 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline bool	*get_forks(void)
{
	static bool	forks[MAX_PHILOSOPHER];

	return (&forks[0]);
}

void	*init_forks(void)
{
	t_param	*params;
	bool	*forks;
	int32_t	i;

	i = 0;
	params = get_params();
	forks = get_forks();
	while (i < params->num_philo)
	{
		forks[i] = malloc(sizeof(bool));
		if (forks[i] == NULL)
			return (NULL);
		i++;
	}
	return ((void *)forks);
}

void	take_forks(t_philo *ph)
{
	bool			*forks;
	const int32_t	num_philo = get_params()->num_philo;
	const int32_t	time_to_eat = get_params()->time_to_eat;
	uint64_t		prev_meal;

	forks = *get_forks();
	ph->state = HUNGRY;
	prev_meal = ph->last_meal;
	while (!ph->priority)
		usleep(1);
	pthread_mutex_lock(ph->take_forks);
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	ph->last_meal = get_time_stamp();
	if (time_to_eat > ph->last_meal - prev_meal)
	{
		ph->state = DIED;
	}
	ph->state = EATING;
	ph->priority = false;
	pthread_mutex_unlock(ph->take_forks);
}
