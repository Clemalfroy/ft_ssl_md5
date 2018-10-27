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

#ifndef HASHING_H
# define HASHING_H

# include <libft.h>
# include "hashing/md5.h"
# include "hashing/sha256.h"

enum			e_opt
{
	OPT_P = 1 << 1,
	OPT_Q = 1 << 2,
	OPT_R = 1 << 3,
	OPT_S = 1 << 4,
	OPT_DONE = 1 << 5,

};

typedef struct	s_hash{
	uint8_t		flags;
}				t_hash;

typedef int	(*t_algo)(const char *, short);

typedef char*(*t_hashalgo)(const char *);

int				hash_parse(int const ac, char const **argv, t_hash *hash,
					t_algo func);
int				hasher(int const ac, char const **argv, t_algo func);
void			display_hash(char const *hash, char *value, char const *word,
					short flags);
char			*hash_file(const char *str, t_hashalgo func);

#endif
