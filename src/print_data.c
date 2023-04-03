/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/01 15:07:12 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	print_msg(const char *msg, t_philo *ph)
{	
	static pthread_mutex_t	*write;

	if (write == NULL)
		write = ph->data->write;
	if (!should_exit())
	{
		pthread_mutex_lock(write);
		printf(msg, get_relative_time_ms(), ph->name);
		pthread_mutex_unlock(write);
	}
}

inline void	print_msg_time(const char *msg, t_philo *ph, int32_t time)
{	
	static pthread_mutex_t	*write;

	if (write == NULL)
		write = ph->data->write;
	if (!should_exit())
	{
		pthread_mutex_lock(write);
		printf(msg, time, ph->name);
		pthread_mutex_unlock(write);
	}
}

