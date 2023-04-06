/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/06 16:37:03 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*init_threads(void)
{
	pthread_t	*threads;
	int32_t		i;
	t_philo		**phs;
	int32_t		num_philo;

	phs = get_philosophers();
	i = 0;
	num_philo = get_params()->num_philo;
	threads = malloc(num_philo * sizeof(pthread_t));
	get_data()->thread_ids = threads;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_work_even, phs[i]);			
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	i = 1;
	while (i < num_philo)
	{
		pthread_create(&threads[i], NULL, philo_work_odd, phs[i]);
		phs[i]->thread_id = threads[i];
		i += 2;
	}
	return (NULL);
}

// void	*join_threads(void)
// {
// 	pthread_t	*threads;
// 	int32_t		i;
// 	t_data		*data;
// 	int32_t		num_philo;
// 	void		*ret;

// 	i = 0;
// 	ret = NULL;
// 	data = get_data();
// 	num_philo = get_params()->num_philo;
// 	threads = get_data()->thread_ids;
// 	while (i < num_philo)
// 	{
// 		pthread_join(threads[i], &ret);
// 		data->even_count--;
// 		i += 2;
// 	}
// 	i = 1;
// 	while (i < num_philo)
// 	{
// 		pthread_join(threads[i], &ret);
// 		data->odd_count--;
// 		i += 2;
// 	}
// 	return (NULL);
// }