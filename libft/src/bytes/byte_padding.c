/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_padding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	byte_padding(void *block_to_pad, uint8_t *message, uint32_t len)
{
	uint64_t	printed_len;

	ft_bzero(block_to_pad, 128);
	ft_memcpy(block_to_pad, message + len - len % 64, len % 64);
	*((uint8_t*)block_to_pad + len % 64) |= 0x80;
	printed_len = len * 8;
	if (!ft_get_endianness())
		printed_len = swap_int64(printed_len);
	((uint64_t*)block_to_pad)[7 + 8 * ((len % 64) > 64 - 9)] = printed_len;
}