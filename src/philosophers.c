/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 09:33:28 by mroy             ###   ########.fr       */
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
	cur_time = get_time_stamp_ms();
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

	if (meal_authorization == NULL)
	{
		meal_authorization = ph->data->meal_authorization;
		time_to_die = ph->params->time_to_die * 1000;
		time_to_eat = ph->params->time_to_eat * 1000;
	}
	prev_meal = ph->last_meal * 1000;
	pthread_mutex_lock(meal_authorization);
	if (time_to_die < (ph->last_meal * 1000) - prev_meal)
	{
		print_msg("%i %i died\n", ph);
		ph->data->exit_threads = true;
	}
	else
		 ph->last_meal = print_msg("%i %i is eating\n", ph);
	pthread_mutex_unlock(meal_authorization);
	two_stage_sleep(time_to_eat, (ph->last_meal  + time_to_eat) * 1000);
}

static inline void	sleeping(t_philo *ph)
{
	static int32_t	time_to_sleep;
	int32_t			time;

	if (time_to_sleep == 0)
		time_to_sleep = (ph->params->time_to_sleep * 1000);	
	time = print_msg("%i %i is sleeping\n", ph);
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
	if (wait_queue == NULL)
		wait_queue = ph->data->even_queue;
	while (i < must_eat && !should_exit())
	{
		pthread_mutex_lock(ph->forks_auth);
		take_forks(ph);
		pthread_mutex_unlock(ph->forks_auth);
		ph->forks_taken = true;		
		eating(ph);
		ph->forks_taken = false;
		sleeping(ph);
		fifo_concurrent_put(wait_queue, (void *)ph);
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
	if (wait_queue == NULL)
		wait_queue = ph->data->odd_queue;
	while (i < must_eat && !should_exit())
	{
		pthread_mutex_lock(ph->forks_auth);
		take_forks(ph);
		pthread_mutex_unlock(ph->forks_auth);
		ph->forks_taken = true;		
		eating(ph);
		ph->forks_taken = false;		
		sleeping(ph);
		fifo_concurrent_put(wait_queue, (void *)ph);
		thinking(ph);
		i++;
	}
	return (NULL);
}
