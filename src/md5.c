#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/md5.h"

int md5(const char *str, short opt) {
	(void)str;
	(void)opt;

	ft_putf(1, "%s", str);

	return (EXIT_SUCCESS);
}