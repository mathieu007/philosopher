/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/01 18:02:57 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *ph)
{
	pthread_mutex_lock(ph->left_fork);
	print_msg("%i %i has taken a fork\n", ph);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	print_msg("%i %i has taken a fork\n", ph);
	pthread_mutex_unlock(ph->right_fork);
}
