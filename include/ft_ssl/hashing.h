#ifndef HASING_H
# define HASING_H

#include <libft.h>

enum			e_opt
{
	OPT_P = 1 << 1,
	OPT_Q = 1 << 2,
	OPT_R = 1 << 3,
	OPT_S = 1 << 4,

};

typedef struct	s_hash{
	u8 			flags;
}				t_hash;

typedef int (*t_algo)(const char *, short);

int hash_parse(int const ac, char const **argv, t_hash *hash, t_algo func);
int hasher(int const ac, char const **argv, t_algo func);


#include "hashing/md5.h"
#include "hashing/sha256.h"

#endif