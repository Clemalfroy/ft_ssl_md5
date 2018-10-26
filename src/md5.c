#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/md5.h"

int md5(const char *str, short opt) {
	display_hash("MD5", "as5d56sa4d", str, opt);
	return (EXIT_SUCCESS);
}