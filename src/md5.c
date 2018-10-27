/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/md5.h"

#include <stdio.h>

static uint32_t g_deltas[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t g_constants[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

#define F(B, C, D) ((B) & (C)) | (~(B) & (D))
#define G(B, C, D) ((B) & (D)) | ((C) & ~(D))
#define H(B, C, D) (B) ^ (C) ^ (D)
#define I(B, C, D) (C) ^ (B | ~(D))

static void	md5_padding(void *block_to_pad, uint8_t *message, uint32_t len)
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

static void	md5_round(uint32_t *block_states, uint32_t *block)
{
	uint32_t	i;
	uint32_t	tmp_f;
	uint32_t	tmp_g;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			tmp_f = F(block_states[1], block_states[2], block_states[3]);
			tmp_g = i;
		}
		else if (i < 32)
		{
			tmp_f = G(block_states[1], block_states[2], block_states[3]);
			tmp_g = (i * 5 + 1) % 16;
		}
		else if (i < 48)
		{
			tmp_f = H(block_states[1], block_states[2], block_states[3]);
			tmp_g = (i * 3 + 5) % 16;
		}
		else
		{
			tmp_f = I(block_states[1], block_states[2], block_states[3]);
			tmp_g = (i * 7) % 16;
		}
		tmp_f += block_states[0] + g_constants[i] + block[tmp_g];
		block_states[0] = block_states[3];
		block_states[3] = block_states[2];
		block_states[2] = block_states[1];
		block_states[1] += left_rotate_32(tmp_f, g_deltas[i]);
		i++;
	}
}

static void	md5_loop(uint32_t *states, uint8_t *message,
	uint8_t *last_block, uint32_t len)
{
	uint32_t	chunk_nbr;
	uint32_t	i;
	uint32_t	block_states[4];
	uint64_t	extra_rounds;

	chunk_nbr = len / 64;
	i = 0;
	while (i < chunk_nbr)
	{
		block_states[0] = states[0];
		block_states[1] = states[1];
		block_states[2] = states[2];
		block_states[3] = states[3];
		md5_round(block_states, (uint32_t*)(void*)(message + i * 64));
		states[0] += block_states[0];
		states[1] += block_states[1];
		states[2] += block_states[2];
		states[3] += block_states[3];
		i++;
	}
	i = 0;
	extra_rounds = 1 + !!((len % 64) > (64 - 9));
	while (i < extra_rounds)
	{
		block_states[0] = states[0];
		block_states[1] = states[1];
		block_states[2] = states[2];
		block_states[3] = states[3];
		md5_round(block_states, (uint32_t*)(void*)(last_block + i * 64));
		states[0] += block_states[0];
		states[1] += block_states[1];
		states[2] += block_states[2];
		states[3] += block_states[3];
		i++;
	}
}

uint32_t	*md5_algo(const char *str)
{
	static uint8_t	last_block[128];
	uint8_t			*message;
	uint32_t		states[4];
	uint32_t		*digest;

	message = (uint8_t*)ft_strdup(str);
	states[0] = 0x67452301;
	states[1] = 0xefcdab89;
	states[2] = 0x98badcfe;
	states[3] = 0x10325476;
	md5_padding(last_block, message, ft_strlen(str));
	md5_loop(states, message, last_block, ft_strlen(str));
	if (!(digest = malloc(16)))
		return (NULL);
	ft_memcpy(digest, states, 16);
	free(message);
	return (digest);
}

int			md5(const char *str, short opt)
{
	uint32_t	*hash;

	if (!(opt & OPT_S))
	{
		if ((hash = hash_file(str, md5_algo)) == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		if ((hash = md5_algo(str)) == NULL)
			return (EXIT_FAILURE);
	}
	display_hash("MD5", hash, str, opt);
	return (EXIT_SUCCESS);
}
