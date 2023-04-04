/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/04 10:17:09 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	print_msg(const char *msg, t_philo *ph)
{	
	static pthread_mutex_t	*write;
	int32_t					time;

	if (write == NULL)
		write = ph->data->write;
	time = 0;
	if (!should_exit())
	{		
		pthread_mutex_lock(write);
		time = get_relative_time_ms();
		printf(msg, time, ph->name);
		pthread_mutex_unlock(write);
	}
	return (time);
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

