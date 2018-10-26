#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/md5.h"

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