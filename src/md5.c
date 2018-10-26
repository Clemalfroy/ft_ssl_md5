#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/md5.h"

static uint32_t r[64] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

char *md5_algo(char *str) {
	return str;
}

int md5(const char *str, short opt) {
	char *hash;

	if (!(opt & OPT_S)) {
		if ((hash = hash_file(str, md5_algo)) == NULL)
			return (EXIT_FAILURE);
	}
	else {
		hash = md5_algo(ft_strdup(str));
	}
	display_hash("MD5", hash, str, opt);
	return (EXIT_SUCCESS);
}