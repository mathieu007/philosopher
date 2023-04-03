/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/26 10:06:20 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline int32_t	next_ph(const int32_t i, const int32_t philo_count)
{
	return ((i + 1) % philo_count);
}

inline int32_t	prev_ph(const int32_t i, const int32_t philo_count)
{
	return (((i - 1) + philo_count) % philo_count);
}
