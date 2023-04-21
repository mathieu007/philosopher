/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:51:17 by math              #+#    #+#             */
/*   Updated: 2023/04/21 10:41:06 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

bool	is_odd(int32_t num)
{
	if (num % 2 == 0)
		return (false);
	return (true);
}

bool	is_even(int32_t num)
{
	if (num % 2 == 0)
		return (true);
	return (false);
}

inline void	sleeper(int32_t end_time)
{	
	int32_t	time;

	time = 101;
	while (time - 100 > 0)
	{
		time = end_time - get_time_stamp_mc();
		if (time > 0)
			usleep(time / 2);
	}
	if (time > 0)
		usleep(time);
}
