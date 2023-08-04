/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/08/04 10:33:51 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline void	inner_philo_even(t_philo *ph, t_data *data)
{
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	save_msg(" has taken a fork\n", ph, data);
	save_msg(" has taken a fork\n", ph, data);
	eating(ph, data);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
	sleeping(ph, data);
	thinking(ph, data);
}

void	*philo_even_work(void *philo)
{
	t_philo	*ph;
	t_data	*data;
	int32_t	eat_count;

	ph = (t_philo *)philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	ph->last_action = ph->last_think - ph->base_time;
	ph->death_time = ph->last_action + ph->time_to_die;
	while (eat_count > 0 && ph->exit_status != 1)
	{
		inner_philo_even(ph, data);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}

static inline void	inner_philo_odd(t_philo *ph, t_data *data)
{
	pthread_mutex_lock(ph->right_fork);
	pthread_mutex_lock(ph->left_fork);
	save_msg(" has taken a fork\n", ph, data);
	save_msg(" has taken a fork\n", ph, data);
	eating(ph, data);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	sleeping(ph, data);
	thinking(ph, data);
}

void	*philo_odd_work(void *philo)
{
	t_philo	*ph;
	t_data	*data;
	int32_t	eat_count;

	ph = (t_philo *)philo;
	data = ph->data;
	eat_count = ph->params->must_eat;
	pthread_mutex_lock(data->write);
	data->threads_ready++;
	pthread_mutex_unlock(data->write);
	pthread_mutex_lock(ph->start_simulation);
	ph->last_think = ph->start_time;
	ph->last_action = ph->last_think - ph->base_time;
	ph->death_time = ph->last_action + ph->time_to_die;
	while (eat_count && ph->exit_status != 1)
	{
		inner_philo_odd(ph, data);
		eat_count--;
	}
	pthread_mutex_unlock(ph->start_simulation);
	return (&(ph->exit_status));
}
