/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 18:10:48 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_philosophers(void)
{
	t_param	*params;
	int32_t	i;
	t_philo	**phs;
	t_data 	*data;
	
	i = 0;
	data = get_data();
	params = get_params();
	phs = malloc(sizeof(t_philo *) * (params->num_philo));
	while (i < params->num_philo)
	{
		phs[i] = malloc(sizeof(t_philo));
		if (phs[i] == NULL)
			return (NULL);
		phs[i]->params = get_params();
		phs[i]->data = data;
		phs[i]->position = i;
		phs[i]->name = i + 1;
		phs[i]->eat_count = 0;
		phs[i]->last_meal = -1;
		phs[i]->forks_taken = false;
		i++;
	}	
	data->philos = phs;
	return (NULL);
}

static inline void	two_stage_sleep(int32_t time_to_sleep, int32_t end_time)
{	
	int32_t	total2;
	int32_t	cur_time;

	usleep(time_to_sleep - 5000);
	cur_time = get_relative_time_mc();
	total2 = end_time - cur_time;
	if (total2 > 0)
		usleep(total2);
}

static void	eating(t_philo *ph)
{
	static __thread pthread_mutex_t	*meal_authorization;
	static __thread int32_t			time_to_die;
	static __thread int32_t			time_to_eat;
	static __thread t_data			*data;
	int32_t							prev_meal;
	int32_t							last_meal;

	if (meal_authorization == NULL)
	{
		data  = ph->data;
		meal_authorization = data->meal_authorization;
		time_to_die = ph->params->time_to_die * 1000;
		time_to_eat = ph->params->time_to_eat * 1000;
		
	}
	prev_meal = ph->last_meal * 1000;
	pthread_mutex_lock(meal_authorization);
	last_meal = get_relative_time_ms();
	if (should_exit_ph(ph) || (time_to_die < (last_meal * 1000) - prev_meal))
	{
		print_msg("%i %i died\n", ph);
		data->exit_threads = true;
	}
	else
		last_meal = print_msg("%i %i is eating\n", ph);
	pthread_mutex_unlock(meal_authorization);
	ph->last_meal = last_meal;
	two_stage_sleep(time_to_eat, (ph->last_msg * 1000) + time_to_eat);
}

static inline void	sleeping(t_philo *ph)
{
	static __thread int32_t	time_to_sleep;
	int32_t			time;

	if (time_to_sleep == 0)
		time_to_sleep = (ph->params->time_to_sleep * 1000);
	time = print_msg("%i %i is sleeping\n", ph);
	two_stage_sleep(time_to_sleep, ph->last_msg * 1000 + time_to_sleep);
}

static inline void	thinking(t_philo *ph)
{
	print_msg("%i %i is thinking\n", ph);
}

void	*philo_work_even(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	int32_t			must_eat;
	static __thread t_fifo	*wait_queue;
	static __thread t_data	*data;

	i = 0;
	ph = (t_philo *) philo;
	data = ph->data;
	must_eat = ph->params->must_eat;
	if (wait_queue == NULL)
		wait_queue = data->even_queue;
	while (i < must_eat && !should_exit_ph(ph))
	{
		pthread_mutex_lock(ph->forks_auth);
		pthread_mutex_unlock(ph->forks_auth);		
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->forks_taken = true;
		take_forks(ph);
		if (i + 1 < must_eat)
			fifo_concurrent_put(wait_queue, (void *)ph);
		eating(ph);
		ph->forks_taken = false;
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
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
	static __thread t_fifo	*wait_queue;
	static __thread t_data	*data;

	i = 0;
	ph = (t_philo *) philo;
	data = ph->data;
	must_eat = ph->params->must_eat;
	if (wait_queue == NULL)
		wait_queue = data->odd_queue;
	while (i < must_eat)
	{
		pthread_mutex_lock(ph->forks_auth);
		pthread_mutex_unlock(ph->forks_auth);
		pthread_mutex_lock(ph->left_fork);
		pthread_mutex_lock(ph->right_fork);
		ph->forks_taken = true;
		take_forks(ph);
		if (i + 1 < must_eat)
			fifo_concurrent_put(wait_queue, (void *)ph);
		eating(ph);
		ph->forks_taken = false;
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		sleeping(ph);
		thinking(ph);
		i++;
	}
	return (NULL);
}
