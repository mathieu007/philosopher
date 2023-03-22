/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/22 10:30:31 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline uint64_t	print_msg(const char *msg, t_philo *ph)
{
	pthread_mutex_lock(get_data()->meal_authorization);
	printf(msg, get_relative_time(), ph->name);
	pthread_mutex_unlock(get_data()->meal_authorization);
}
