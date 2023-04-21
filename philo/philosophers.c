/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/21 12:20:41 by mroy             ###   ########.fr       */
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

static inline void	inner_philo_even(t_philo *ph, t_data *data,
	const int32_t time_to_eat, const int32_t time_to_sleep)
{	
	pthread_mutex_lock(ph->left_fork);
	print_msg(" has taken a fork\n", ph, data);
	pthread_mutex_lock(ph->right_fork);
	print_msg(" has taken a fork\n", ph, data);
	eating(ph, data, time_to_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
}

void	*philo_even_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int32_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat * 1000;
	const int32_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep * 1000;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	while (eat_count > 0 && ph->exit_status != 1)
	{	
		inner_philo_even(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}

static inline void	inner_philo_odd(t_philo *ph, t_data *data,
	int32_t time_to_eat, int32_t time_to_sleep)
{
	pthread_mutex_lock(ph->right_fork);
	print_msg(" has taken a fork\n", ph, data);
	pthread_mutex_lock(ph->left_fork);
	print_msg(" has taken a fork\n", ph, data);
	eating(ph, data, time_to_eat);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	sleeping(ph, data, time_to_sleep);
	thinking(ph, data);
}

void	*philo_odd_work(void *philo)
{
	t_philo			*ph;
	t_data			*data;
	int32_t			eat_count;
	const int32_t	time_to_eat
		= ((t_philo *)philo)->params->time_to_eat * 1000;
	const int32_t	time_to_sleep
		= ((t_philo *)philo)->params->time_to_sleep * 1000;

	ph = (t_philo *) philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	while (eat_count && ph->exit_status != 1)
	{
		inner_philo_odd(ph, data, time_to_eat, time_to_sleep);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}
