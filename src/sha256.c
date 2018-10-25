#include "ft_ssl/hashing.h"
#include "ft_ssl/hashing/sha256.h"

int sha256(const char *str, short opt) {
	(void)str;
	(void)opt;
	
	ft_putf(1, "%s", str);

	return (EXIT_SUCCESS);
}