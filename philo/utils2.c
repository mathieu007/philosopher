/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 09:51:17 by math              #+#    #+#             */
/*   Updated: 2023/04/19 15:20:43 by mroy             ###   ########.fr       */
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
