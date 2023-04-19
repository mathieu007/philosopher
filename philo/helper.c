/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/19 15:19:23 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	prev_ph(const int32_t i, const int32_t philo_count)
{
	return (((i - 1) + philo_count) % philo_count);
}

void	set_constant_char(const char val, const char *addr)
{
	*((char *)addr) = val;
}

void	set_constant(const int32_t val, const int32_t *addr)
{
	*((int32_t *)addr) = val;
}

void	set_constant64(const int64_t val, const int64_t *addr)
{
	*((int64_t *)addr) = val;
}
