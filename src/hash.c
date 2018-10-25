#include "ft_ssl/hashing.h"

int string_hash(const char *str, t_hash *hash, t_algo func) {
	hash->flags |= OPT_S;
	if (!func(str, hash->flags))
		return (0);
	hash->flags &= OPT_S;
	return (1);
}

int hasher(int const ac, char const **argv, t_algo func) {
	t_hash hash;
	i32 i;
	char *input;

	input = NULL;
	if ((i = hash_parse(ac, argv, &hash, func)) <= 0)
		return (EXIT_FAILURE);
	if (i == ac && ft_read_all(STDIN_FILENO, &input)) {
		string_hash(input, &hash, func);
		free(input);
	}
	while (i++ < ac - 1)
		func(argv[i], hash.flags);
    return (EXIT_SUCCESS);
}

int hash_parse(int const ac, char const **argv, t_hash *hash, t_algo func) 
{
	int		opt;
	char 	*input;

	input = NULL;
	g_optind = 2;
	while ((opt = ft_getopt(ac, argv, "pqrs:")) != -1)
		if (opt == 'p') {
			if (!ft_read_all(STDIN_FILENO, &input))
				return (-1);
			hash->flags & OPT_P ? string_hash("\0", hash, func)
			: string_hash(input, hash, func);
			hash->flags |= OPT_P;
			free(input);
		}
		else if (opt == 's')
			string_hash(g_optarg, hash, func);
		else if (opt == 'q')
            hash->flags |= OPT_Q;
        else if (opt == 'r')
            hash->flags |= OPT_R;
		else
			return (-1);
	return (g_optind); 
}

