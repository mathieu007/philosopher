/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitpack8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/03/18 08:56:54 by math             ###   ########.fr       */
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
			*(out++) = ((*in) >> in_word_pointer) % (1U << 8);
			in_word_pointer += 8;
		}
		outer++;
		in++;
	}
}

void pack8(const uint32_t *in, uint32_t *out) {
  for(uint outer=0; outer< 8 ;++outer) {
    for( uint inwordpointer =  0 ;inwordpointer<32; inwordpointer +=  8 )
      *out |= ((*(in++))   % (1U << 8 )  ) << inwordpointer  ;
    ++out;
  }
}