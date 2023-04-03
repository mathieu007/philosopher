/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/31 15:54:06 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

inline t_data	*get_data(void)
{
	static t_data	data[1];
	static t_data	*ret = &data[0];

	return (ret);
}

inline t_philo	**get_philosophers(void)
{
	return (get_data()->philos);
}

inline bool	should_exit(void)
{
	return (get_data()->exit_threads);
}
