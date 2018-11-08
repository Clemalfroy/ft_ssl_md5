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

#include "ft_ssl/hashing/md5.h"

#define A 0
#define B 1
#define C 2
#define D 3

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

static void	md5_round(uint32_t *bk_states, uint32_t *block)
{
	int32_t		i;
	uint32_t	tmp_f;
	uint32_t	tmp_g;

	i = -1;
	while (++i < 64)
	{
		if (i < 16 && (tmp_f = F(bk_states[B], bk_states[C], bk_states[D])))
			tmp_g = i;
		else if (i < 32
		&& (tmp_f = G(bk_states[B], bk_states[C], bk_states[D])))
			tmp_g = (i * 5 + 1) % 16;
		else if (i < 48
		&& (tmp_f = H(bk_states[B], bk_states[C], bk_states[D])))
			tmp_g = (i * D + 5) % 16;
		else if (i < 64
		&& (tmp_f = I(bk_states[B], bk_states[C], bk_states[D])))
			tmp_g = (i * 7) % 16;
		tmp_f += bk_states[A] + g_constants[i] + block[tmp_g];
		bk_states[A] = bk_states[D];
		bk_states[D] = bk_states[C];
		bk_states[C] = bk_states[B];
		bk_states[B] += left_rotate_32(tmp_f, g_deltas[i]);
	}
}

static void	md5_loop(uint32_t *states, uint8_t *message,
	uint8_t *last_block, uint32_t len)
{
	uint32_t	chunk_nbr;
	uint32_t	block_states[4];
	uint64_t	extra_rounds;
	uint32_t	i;
	uint32_t	j;

	i = -1;
	chunk_nbr = len / 64;
	while (++i < chunk_nbr && (j = -1))
	{
		ft_memcpy(block_states, states, sizeof(block_states));
		md5_round(block_states, (uint32_t*)(void*)(message + i * 64));
		while (++j < 4)
			states[j] += block_states[j];
	}
	i = -1;
	extra_rounds = 1 + ((len % 64) > (64 - 9));
	while (++i < extra_rounds && (j = -1))
	{
		ft_memcpy(block_states, states, sizeof(block_states));
		md5_round(block_states, (uint32_t*)(void*)(last_block + i * 64));
		while (++j < 4)
			states[j] += block_states[j];
	}
}

uint32_t	*md5_algo(const char *str)
{
	static uint8_t	last_block[128];
	uint8_t			*message;
	uint32_t		states[4];
	uint32_t		*digest;
	size_t			len;

	len = ft_strlen(str);
	message = (uint8_t*)ft_strdup(str);
	states[A] = 0x67452301;
	states[B] = 0xefcdab89;
	states[C] = 0x98badcfe;
	states[D] = 0x10325476;
	byte_padding(last_block, message, len);
	md5_loop(states, message, last_block, len);
	if (!(digest = malloc(sizeof(states))))
		return (NULL);
	ft_memcpy(digest, states, sizeof(states));
	free(message);
	return (digest);
}

int			md5(const char *str, t_hash *hashopt)
{
	uint32_t	*hash;

	hashopt->size = 16;
	hashopt->swap_endian = 1;
	if (!(hashopt->flags & OPT_S))
	{
		if ((hash = hash_file(str, md5_algo)) == NULL)
			return (EXIT_FAILURE);
	}
	else if ((hash = md5_algo(str)) == NULL)
		return (EXIT_FAILURE);
	display_hash("MD5", hash, str, hashopt);
	return (EXIT_SUCCESS);
}
