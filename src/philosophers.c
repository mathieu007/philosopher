/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/13 17:07:43 by mroy             ###   ########.fr       */
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
		phs[i]->is_auth = false;
		phs[i]->died = false;
		i++;
	}	
	data->philos = phs;
	return (NULL);
}

static void	two_stage_sleep(t_data *data, int32_t time_to_sleep,
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

static void	eating(t_philo *ph, t_data *data)
{
	const int32_t	time_to_die = ph->params->time_to_die * 1000;
	const int32_t	time_to_eat = ph->params->time_to_eat * 1000;
	int32_t			prev_meal;

	prev_meal = ph->last_meal;
	if (time_to_die < get_relative_time_mc(data) - prev_meal)
		print_die_msg("%i %i died\n", ph, data);
	else
		ph->last_meal = print_msg("%i %i is eating\n", ph, data);
	two_stage_sleep(data, time_to_eat, ph->last_meal + time_to_eat);
}

static void	sleeping(t_philo *ph, t_data *data)
{
	const int32_t	time_to_sleep = (ph->params->time_to_sleep * 1000);
	int32_t			sleep_time;

	sleep_time = print_msg("%i %i is sleeping\n", ph, data);
	two_stage_sleep(ph->data, time_to_sleep, sleep_time + time_to_sleep);
}

static void	thinking(t_philo *ph, t_data *data)
{
	print_msg("%i %i is thinking\n", ph, data);
}

void	*philo_even_work(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	t_data			*data;
	int64_t			time;
	const int32_t	eat_count = ((t_philo *)philo)->params->must_eat;
	// const int64_t	time_cycle = ((t_philo *)philo)->params->time_cycle;

	ph = (t_philo *) philo;
	data = ph->data;
	i = 0;
	time = 0;
	while (i < eat_count && ph->exit_status != 1)
	{
		pthread_mutex_lock(ph->process_mutex);
		pthread_mutex_lock(ph->right_fork);
		print_msg("%i %i has taken a fork\n", ph, data);
		pthread_mutex_lock(ph->left_fork);
		print_msg("%i %i has taken a fork\n", ph, data);
		eating(ph, data);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		pthread_mutex_unlock(ph->process_mutex);
		sleeping(ph, data);
		thinking(ph, data);
		i++;
	}
	return (&(ph->exit_status));
}

void	*philo_odd_work(void *philo)
{
	t_philo			*ph;
	int32_t			i;
	t_data			*data;
	int64_t			time;
	const int32_t	eat_count = ((t_philo *)philo)->params->must_eat;
	// const int64_t	time_cycle = ((t_philo *)philo)->params->time_cycle;

	i = 0;
	ph = (t_philo *) philo;
	data = ph->data;
	i = 0;
	ph->is_auth = false;
	time = 0;
	while (i < eat_count && ph->exit_status != 1)
	{
		pthread_mutex_lock(ph->process_mutex);
		pthread_mutex_unlock(ph->process_mutex);
		pthread_mutex_lock(ph->right_fork);
		print_msg("%i %i has taken a fork\n", ph, data);
		pthread_mutex_lock(ph->left_fork);
		print_msg("%i %i has taken a fork\n", ph, data);
		eating(ph, data);
		pthread_mutex_unlock(ph->right_fork);
		pthread_mutex_unlock(ph->left_fork);
		sleeping(ph, data);
		thinking(ph, data);
		i++;
	}
	return (&(ph->exit_status));
}
