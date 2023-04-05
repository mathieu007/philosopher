/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/05 10:43:53 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline void	print_msg(const char *msg, t_philo *ph, int32_t time)
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

