/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/03 07:08:23 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	update_state(void *philo, bool value)
{
	t_philo			*ph;

	ph = (t_philo *)philo;
	ph->forks_taken = value;
}

void	*init_philosophers(void)
{
	t_param	*params;
	int32_t	i;
	t_philo	**phs;

	i = 0;
	params = get_params();
	phs = malloc(sizeof(t_philo *) * (params->num_philo));
	while (i < params->num_philo)
	{
		phs[i] = malloc(sizeof(t_philo));
		if (phs[i] == NULL)
			return (NULL);
		phs[i]->params = get_params();
		phs[i]->data = get_data();
		phs[i]->is_eating = false;
		phs[i]->position = i;
		phs[i]->name = i + 1;
		phs[i]->eat_count = 0;
		phs[i]->last_meal = -1;
		phs[i]->forks_taken = false;
		phs[i]->update_state = &update_state;
		i++;
	}
	get_data()->philos = phs;
	return (NULL);
}

static int32_t	eating(t_philo *ph)
{
	static pthread_mutex_t	*meal_authorization;
	static int32_t			time_to_die;
	static int32_t			time_to_eat;
	int32_t					prev_meal;
	int32_t					last_meal;

	prev_meal = ph->last_meal;
	if (meal_authorization == NULL)
	{
		meal_authorization = ph->data->meal_authorization;
		time_to_die = ph->params->time_to_die * 1000;
		time_to_eat = ph->params->time_to_eat * 1000;
	}
	pthread_mutex_lock(meal_authorization);
	last_meal = get_relative_time_mc();
	if (time_to_die < last_meal - prev_meal)
	{
		print_msg("%i %i died\n", ph);
		ph->data->exit_threads = true;
	}
	else
		print_msg_time("%i %i is eating\n", ph, last_meal / 1000);
	pthread_mutex_unlock(meal_authorization);
	usleep(time_to_eat);
	return (last_meal);
}

static inline void	sleeping(t_philo *ph)
{
	static int32_t	time_to_sleep;

	if (time_to_sleep == 0)
		time_to_sleep = (ph->params->time_to_sleep * 1000);
	print_msg("%i %i is sleeping\n", ph);
	usleep(time_to_sleep);
}

static inline void	thinking(t_philo *ph)
{
	print_msg("%i %i is thinking\n", ph);
}

static inline bool	should_swap(void *current_head, void *new_value)
{
	if (((t_philo *)current_head)->last_meal > ((t_philo *)new_value)->last_meal)
	{
		return (true);
	}
		
	return (false);
}

void	*philo_work(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	int32_t			must_eat;
	static t_fifo	*wait_queue;

	i = 0;
	ph = (t_philo *) philo;
	must_eat = ph->params->must_eat;
	if (wait_queue == NULL)
		wait_queue = ph->data->wait_queue;
	while (i < must_eat && !should_exit())
	{
		pthread_mutex_lock(ph->forks_auth);
		take_forks(ph);
		ph->forks_taken = true;
		pthread_mutex_unlock(ph->forks_auth);
		ph->last_meal = eating(ph);
		ph->forks_taken = false;
		sleeping(ph);
		fifo_concurrent_put_swap(wait_queue, (void *)ph, &should_swap);
		thinking(ph);
		i++;
	}
	return (NULL);
}
