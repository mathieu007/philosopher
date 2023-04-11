/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/10 13:57:30 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int32_t	print_msg(const char *msg, const t_philo *ph, const t_data *data)
{	
	int32_t	time;

	time = 0;
	if (!ph->exit_thread)
	{
		pthread_mutex_lock(data->write);
		time = get_relative_time_mc(data);
		printf(msg, time / 1000, ph->name);
		pthread_mutex_unlock(data->write);
	}
	return (time);
}

