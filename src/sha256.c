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

#include "ft_ssl/hashing/sha256.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

// static uint32_t const	g_constants[64] = {
// 0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,
// 0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,
// 0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,
// 0x4a7484aa,0x5cb0a9dc,0x76f988da,0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,
// 0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b70a85,0x2e1b2138,0x4d2c6dfc,
// 0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,0xa2bfe8a1,0xa81a664b,
// 0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,0x19a4c116,
// 0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
// 0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,
// 0xc67178f2 };

static void	sha256_padding(void *block_to_pad, uint8_t *message, uint32_t len)
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

uint32_t	*sha256_algo(const char *str)
{
	static uint8_t	last_block[128];
	uint8_t			*message;
	uint32_t		states[8];
	uint32_t		*digest;
	size_t			len;

	message = (uint8_t*)ft_strdup(str);
	states[A] = 0x6a09e667;
	states[B] = 0xbb67ae85;
	states[C] = 0x3c6ef372;
	states[D] = 0xa54ff53a;
	states[E] = 0x510e527f;
	states[F] = 0x9b05688c;
	states[G] = 0x1f83d9ab;
	states[H] = 0x5be0cd19;
	len = ft_strlen(str);
	sha256_padding(last_block, message, len);
	//sha256_loop(states, message, (uint32_t*)last_block, len);
	if (!(digest = malloc(sizeof(states))))
		return (NULL);
	ft_memcpy(digest, states, sizeof(states));
	return (digest);
}

int			sha256(const char *str, t_hash *hashopt)
{
	uint32_t *hash;

	hashopt->size = 32;
	hashopt->swap_endian = ft_get_endianness() ? 1 : 0;
	if (!(hashopt->flags & OPT_S))
	{
		if ((hash = hash_file(str, sha256_algo)) == NULL)
			return (EXIT_FAILURE);
	}
	else
		hash = sha256_algo(ft_strdup(str));
	display_hash("SHA256", hash, str, hashopt);
	return (EXIT_SUCCESS);
}
