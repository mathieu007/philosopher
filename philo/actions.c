/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/05/05 15:32:37 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	three_stage_sleep(const t_philo *ph, int32_t time_to_sleep,
	int32_t end_time)
{	
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
	}
	if (time > 0)
		usleep(time);
}

static inline void	think_sleeper(const t_philo *ph, int32_t end_time)
{	
	int32_t time;
	
	time = (end_time - get_relative_time_mc(ph)) / 2;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph) - 500;			
		if (time > 0)
			usleep(time);		
	}
	time = end_time - get_relative_time_mc(ph);
	if (time > 0)
		usleep(time);
}

inline int32_t	two_stage_sleep(const t_philo *ph, int32_t time_to_sleep, int32_t end_time)
{	
	int32_t	time;

	time = time_to_sleep - 5000;
	if (time > 0)
		usleep(time);
	while (time - 500 > 0)
	{
		time = end_time - get_relative_time_mc(ph);
		if (time > 0)
			usleep(time / 2);
	}
	return (time);
}

inline void	eating(t_philo *ph, t_data *data, const int32_t time_to_eat, const int32_t time_to_die)
{
	int32_t	time;
	int32_t	death_time;
		
	save_eat(ph, data, time_to_die);
	death_time = ph->last_meal + time_to_die;
	if (ph->last_action + time_to_eat > death_time)
	{
		write(1, "died eating\n", 13);
		usleep((ph->last_action + time_to_eat) - death_time);
		save_die_msg(ph, data);
	}
	time = two_stage_sleep(ph, time_to_eat, ph->last_meal + time_to_eat);
	pthread_mutex_lock(data->write);
	*(ph->left_fork_taken) = false;
	*(ph->right_fork_taken) = false;
	pthread_mutex_unlock(data->write);
	if (time > 0)
		usleep(time);
}

inline void	sleeping(t_philo *ph, t_data *data, const int32_t time_to_sleep, const int32_t death_time)
{
	save_msg(" is sleeping\n", ph, data);
	if (ph->last_action + time_to_sleep > death_time)
	{
		write(1, "died sleeping\n", 15);
		usleep((ph->last_action + time_to_sleep) - death_time);
		save_die_msg(ph, data);
	}
	three_stage_sleep(ph, time_to_sleep, ph->last_action + time_to_sleep);
}

inline void	thinking(t_philo *ph, t_data *data, const int32_t death_time)
{
	const int32_t	time_cycle = ph->params->time_cycle;

	save_msg(" is thinking\n", ph, data);
	if (ph->last_action > death_time)
	{
		write(1, "died thinking\n", 15);
		usleep(ph->last_action - death_time);
		save_die_msg(ph, data);
	}
	ph->last_think += (int64_t)time_cycle;
	think_sleeper(ph, (int32_t)(ph->last_think - ph->base_time));	
}
