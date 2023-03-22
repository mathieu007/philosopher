/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/22 13:02:09 by mroy             ###   ########.fr       */
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

static void	sleeping(t_philo *ph)
{
	print_msg("%lu %i is sleeping\n", ph);
	usleep(get_params()->time_to_sleep);
}

static void	thinking(t_philo *ph)
{
	print_msg("%lu %i is thinking\n", ph);
	usleep(get_params()->time_to_sleep);
}

void	*philo_work(void *philo)
{
	t_philo			*ph;
	pthread_mutex_t	*authorized;
	uint64_t		prev_meal;

	authorized = get_data()->forks_authorization;
	ph = (t_philo *) philo;
	while (true)
	{
		pthread_mutex_lock(authorized);
		if (!ph->is_authorized)
		{
			pthread_mutex_unlock(authorized);
			continue ;
		}
		prev_meal = ph->last_meal;
		take_forks(ph);
		ph->is_authorized = false;
		pthread_mutex_unlock(authorized);
		eating(ph, prev_meal);
		sleeping(ph);
		thinking(ph);
	}
}
