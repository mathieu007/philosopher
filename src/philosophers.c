/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 15:51:15 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_philosophers(void)
{
	t_param	*params;
	t_philo	**philos;
	int32_t	i;

	params = get_params();
	i = 0;
	philos = get_philosophers();
	while (i < params->num_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (NULL);
		i++;
	}
	return ((void *)philos);
}

static void	eating(t_philo *ph, uint64_t prev_meal)
{
	pthread_mutex_lock(get_data()->meal_authorization);
	ph->last_meal = get_time_stamp();
	if (get_params()->time_to_eat > ph->last_meal - prev_meal)
	{
		print_msg("%lu %i died\n", ph);
		free_exit();
	}
	else
		print_msg("%lu %i is eating\n", ph);
	pthread_mutex_unlock(get_data()->meal_authorization);
	usleep(get_params()->time_to_eat);
}

static inline void	sleeping(t_philo *ph)
{
	print_msg("%lu %i is sleeping\n", ph);
	usleep(get_params()->time_to_sleep);
}

static inline void	thinking(t_philo *ph)
{
	print_msg("%lu %i is thinking\n", ph);
}

void	*philo_work(void *philo)
{
	t_philo			*ph;
	uint64_t		prev_meal;

	ph = (t_philo *) philo;
	while (true)
	{
		pthread_mutex_lock(ph->forks_auth);
		prev_meal = ph->last_meal;
		ph->is_authorized = false;
		take_forks(ph);
		pthread_mutex_unlock(ph->forks_auth);
		eating(ph, prev_meal);
		sleeping(ph);
		thinking(ph);
	}
}
