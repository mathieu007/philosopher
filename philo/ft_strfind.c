/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:16:34 by mathieu           #+#    #+#             */
/*   Updated: 2023/08/03 18:40:50 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

char	*ft_strfind(char *src, const char *to_search)
{
	int32_t	i;
	int32_t	j;

	if (!src || !to_search)
		return (src);
	j = 0;
	while (src[j])
	{
		i = 0;
		while (to_search[i] && src[j + i] && to_search[i] == src[j + i])
			i++;
		if (to_search[i] == '\0')
			return (&src[j]);
		j++;
	}
	return (src);
}
