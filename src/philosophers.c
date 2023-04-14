/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/14 10:37:49 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_philosophers(void)
{
	t_param	*params;
	int32_t	i;
	t_philo	**phs;
	t_data	*data;

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
		phs[i]->last_meal = 0;
		phs[i]->exit_status = 0;
		i++;
	}	
	data->philos = phs;
	return (NULL);
}

void	two_stage_sleep(const t_data *data, int32_t time_to_sleep,
	int32_t end_time)
{	
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	time = end_time - get_relative_time_mc(data);
	if (time > 0)
		usleep(time);
}

static void	eating(t_philo *ph)
{
	const int32_t	time_to_eat = ph->params->time_to_eat * 1000;
	int32_t			prev_meal;

	prev_meal = ph->last_meal;
	ph->last_meal = print_eat_or_die(ph, prev_meal);
	two_stage_sleep(data, time_to_eat, ph->last_meal + time_to_eat);
}

static void	sleeping(t_philo *ph)
{
	const int32_t	time_to_sleep = (ph->params->time_to_sleep * 1000);
	int32_t			sleep_time;

	sleep_time = print_msg("%i %i is sleeping\n", ph);
	two_stage_sleep(ph->data, time_to_sleep, sleep_time + time_to_sleep);
}

static void	thinking(t_philo *ph)
{
	const int32_t	time_cycle = ph->params->time_cycle;
	int32_t			time;

	print_msg("%i %i is thinking\n", ph);
	ph->last_think += time_cycle;
	time = ph->last_think - get_relative_time_mc(ph->data);
	if (time > 0)
		usleep(time);
}

void	*philo_even_work(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	t_data			*data;
	const int32_t	eat_count = ((t_philo *)philo)->params->must_eat;

	ph = (t_philo *) philo;
	i = 0;
	data = ph->data;
	pthread_mutex_lock(ph->start_simulation);
	pthread_mutex_lock(data->write);
	if (data->base_time == 0)
		data->base_time = get_time_stamp_mc();
	pthread_mutex_unlock(data->write);
	ph->base_time = data->base_time;
	ph->last_think = get_relative_time_mc(ph);
	while (i < eat_count && ph->exit_status != 1)
	{
		pthread_mutex_lock(ph->left_fork);
		print_msg("%i %i has taken a fork\n", ph);
		pthread_mutex_lock(ph->right_fork);
		print_msg("%i %i has taken a fork\n", ph);
		eating(ph, data);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->right_fork);
		sleeping(ph);
		thinking(ph);
		i++;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}

void	*philo_odd_work(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	t_data			*data;
	const int32_t	eat_count = ((t_philo *)philo)->params->must_eat;

	i = 0;
	ph = (t_philo *) philo;
	i = 0;
	data = ph->data;
	pthread_mutex_lock(ph->start_simulation);
	pthread_mutex_lock(data->write);
	if (data->base_time == 0)
		data->base_time = get_time_stamp_mc();
	pthread_mutex_unlock(data->write);
	ph->base_time = data->base_time;
	ph->last_think = get_relative_time_mc(ph);
	while (i < eat_count && ph->exit_status != 1)
	{
		pthread_mutex_lock(ph->right_fork);
		print_msg("%i %i has taken a fork\n", ph);
		pthread_mutex_lock(ph->left_fork);
		print_msg("%i %i has taken a fork\n", ph);
		eating(ph);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		sleeping(ph);
		thinking(ph);
		i++;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}
