#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/sha256.h"

char *sha256_algo(char *str) {
	return str;
}

int sha256(const char *str, short opt) {
	char *hash;

	if (!(opt & OPT_S)) {
		if ((hash = hash_file(str, sha256_algo)) == NULL)
			return (EXIT_FAILURE);
	}
	else {
		hash = sha256_algo(ft_strdup(str));
	}
	display_hash("SHA256", hash, str, opt);
	return (EXIT_SUCCESS);
}