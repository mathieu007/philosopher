/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 07:19:55 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
		phs[i]->position = i;
		phs[i]->name = i + 1;
		phs[i]->eat_count = 0;
		phs[i]->last_meal = -1;
		phs[i]->forks_taken = false;
		i++;
	}
	get_data()->philos = phs;
	return (NULL);
}

static inline void	two_stage_sleep(int32_t time_to_sleep, int32_t end_time)
{	
	int32_t	total2;
	int32_t	cur_time;

	usleep(time_to_sleep - 10000);
	cur_time = get_relative_time_mc();
	total2 = end_time - cur_time;
	if (total2 > 0)
		usleep(total2);
}

static void	eating(t_philo *ph)
{
	static pthread_mutex_t	*meal_authorization;
	static int32_t			time_to_die;
	static int32_t			time_to_eat;
	int32_t					prev_meal;
	int32_t					last_meal;

	if (meal_authorization == NULL)
	{
		meal_authorization = ph->data->meal_authorization;
		time_to_die = ph->params->time_to_die * 1000;
		time_to_eat = ph->params->time_to_eat * 1000;
	}
	prev_meal = ph->last_meal * 1000;
	last_meal = get_relative_time_mc();
	pthread_mutex_lock(meal_authorization);
	ph->last_meal = last_meal / 1000;
	if (time_to_die < last_meal - prev_meal)
	{
		print_msg("%i %i died\n", ph);
		ph->data->exit_threads = true;
	}
	else
		print_msg_time("%i %i is eating\n", ph, ph->last_meal);
	pthread_mutex_unlock(meal_authorization);
	two_stage_sleep(time_to_eat, last_meal + time_to_eat);
}

static inline void	sleeping(t_philo *ph)
{
	static int32_t	time_to_sleep;
	int32_t			time;

	if (time_to_sleep == 0)
		time_to_sleep = (ph->params->time_to_sleep * 1000);
	time = get_relative_time_ms();
	print_msg_time("%i %i is sleeping\n", ph, time);
	two_stage_sleep(time_to_sleep, (time * 1000) + time_to_sleep);
}

static inline void	thinking(t_philo *ph)
{
	print_msg_time("%i %i is thinking\n", ph, get_relative_time_ms());
}

void	*philo_work_even(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	int32_t			must_eat;
	static t_fifo	*wait_queue;

	i = 0;
	ph = (t_philo *) philo;
	must_eat = ph->params->must_eat;
	*get_thread_philo() = ph;
	if (wait_queue == NULL)
		wait_queue = ph->data->even_queue;
	while (i < must_eat && !should_exit())
	{
		pthread_mutex_lock(ph->forks_auth);
		pthread_mutex_unlock(ph->forks_auth);
		ph->forks_taken = true;
		take_forks(ph);
		eating(ph);
		ph->forks_taken = false;
		fifo_concurrent_put(wait_queue, (void *)ph);
		sleeping(ph);
		thinking(ph);
		i++;
	}
	return (NULL);
}

void	*philo_work_odd(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	int32_t			must_eat;
	static t_fifo	*wait_queue;

	i = 0;
	ph = (t_philo *) philo;
	must_eat = ph->params->must_eat;
	*get_thread_philo() = ph;
	if (wait_queue == NULL)
		wait_queue = ph->data->odd_queue;
	while (i < must_eat && !should_exit())
	{
		pthread_mutex_lock(ph->forks_auth);
		pthread_mutex_unlock(ph->forks_auth);
		ph->forks_taken = true;
		take_forks(ph);
		eating(ph);
		ph->forks_taken = false;
		fifo_concurrent_put(wait_queue, (void *)ph);
		sleeping(ph);
		thinking(ph);
		i++;
	}
	return (NULL);
}
