/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:51:17 by math              #+#    #+#             */
/*   Updated: 2023/05/06 08:52:57 by math             ###   ########.fr       */
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

inline void	sleeper(int64_t end_time)
{	
	int64_t	time;

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
