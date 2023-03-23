/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitpack8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/23 07:46:47 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	unpack8(const uint32_t *in, uint32_t *out)
{	
	uint32_t	outer;
	uint32_t	in_word_pointer;

	outer = 0;
	while (outer < 8)
	{
		in_word_pointer = 0;
		while (in_word_pointer < 32)
		{
			*out = ((*in) >> in_word_pointer) % (1U << 8);
			in_word_pointer += 8;
			out++;
		}
		outer++;
		in++;
	}
}

void	pack8(const uint32_t *in, uint32_t *out)
{
	uint32_t	outer;
	uint32_t	in_word_pointer;

	outer = 0;
	in_word_pointer = 0;
	while (outer < 8)
	{
		while (in_word_pointer < 32)
		{
			*out |= ((*(in++)) % (1U < 8)) << in_word_pointer;
			in_word_pointer += 8;
			out++;
		}
		outer++;
	}
}
