/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 17:57:19 by mroy             ###   ########.fr       */
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
	static t_data	*data;

	if (data == NULL)
		data = get_data();
	return (data->exit_threads || (data->even_count == 0 && data->odd_count == 0));
}

inline bool	should_exit_ph(t_philo *ph)
{
	static __thread t_data	*data;

	if (data == NULL)
		data = ph->data;
	return (data->exit_threads || (data->even_count == 0 && data->odd_count == 0));
}
