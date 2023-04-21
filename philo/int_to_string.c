/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mroy <mroy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:44:52 by math              #+#    #+#             */
/*   Updated: 2023/04/21 09:31:31 by mroy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static uint32_t	digits10(uint64_t v)
{
	if (v < 10)
		return (1);
	if (v < 100)
		return (2);
	if (v < 1000)
		return (3);
	if (v < 1000000000000)
	{
		if (v < 100000000)
		{
			if (v < 1000000)
			{
				if (v < 10000)
					return (4);
				return (5 + (v >= 100000));
			}
			return (7 + (v >= 10000000));
		}
		if (v < 10000000000)
		{
			return (9 + (v >= 1000000000));
		}
		return (11 + (v >= 100000000000));
	}
	return (12 + digits10(v / 1000000000000));
}

inline static size_t	convert_loop(size_t next, uint32_t i,
	uint32_t *value, char *dst)
{
	static const char	digits[201]
		= "0001020304050607080910111213141516171819"
		"2021222324252627282930313233343536373839"
		"4041424344454647484950515253545556575859"
		"6061626364656667686970717273747576777879"
		"8081828384858687888990919293949596979899";

	i = (*value % 100) * 2;
	*value /= 100;
	dst[next] = digits[i + 1];
	dst[next - 1] = digits[i];
	next -= 2;
	return (next);
}

size_t	uint32_to_str(uint32_t value, char *dst)
{
	static const char	digits[201]
		= "0001020304050607080910111213141516171819"
		"2021222324252627282930313233343536373839"
		"4041424344454647484950515253545556575859"
		"6061626364656667686970717273747576777879"
		"8081828384858687888990919293949596979899";
	size_t const		length = digits10(value);
	size_t				next;
	uint32_t			i;

	i = 0;
	next = length - 1;
	while (value >= 100)
		next = convert_loop(next, i, &value, dst);
	if (value < 10)
		dst[next] = '0' + (value);
	else
	{
		i = value * 2;
		dst[next] = digits[i + 1];
		dst[next - 1] = digits[i];
	}
	return (length);
}
