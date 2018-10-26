#include "ft_ssl/hashing.h"

int		string_hash(const char *str, t_hash *hash, t_algo func) {
	hash->flags |= OPT_S;
	if (!func(str, hash->flags))
		return (0);
	hash->flags &= ~OPT_S;
	return (1);
}

int		hasher(int const ac, char const **argv, t_algo func) {
	t_hash hash;
	i32 i;
	char *input;

	input = NULL;
	hash.flags = 0;
	if ((i = hash_parse(ac, argv, &hash, func)) <= 0)
		return (EXIT_FAILURE);
	if (i == ac && (ac <= 2 || (hash.flags & OPT_Q && !(hash.flags & OPT_DONE)))) {
		ft_read_all(STDIN_FILENO, &input);
		hash.flags |= OPT_DONE;
		hash.flags |= OPT_Q;
		string_hash(input, &hash, func);
		free(input);
	}
	hash.flags &= ~OPT_S;
	while (i++ < ac)
	 	func(argv[i - 1], hash.flags);
    return (EXIT_SUCCESS);
}

int		hash_parse(int const ac, char const **argv, t_hash *hash, t_algo func) 
{
	int		opt;
	char 	*input;

	input = NULL;
	g_optind = 2;
	while ((opt = ft_getopt(ac, argv, "pqrs:")) != -1)
		if (opt == 'p') {
			if (!ft_read_all(STDIN_FILENO, &input))
				return (-1);
			hash->flags |= OPT_P;
			string_hash(input, hash, func);
			hash->flags &= ~OPT_P;
			free(input);
		}
		else if (opt == 's' && (hash->flags |= OPT_DONE))
			string_hash(g_optarg, hash, func);
		else if (opt == 'q')
            hash->flags |= OPT_Q;
        else if (opt == 'r')
            hash->flags |= OPT_R;
		else
			return (-1);
	return (g_optind); 
}

void	display_hash(char const *hash, char *value, char const *word, short flags) {
	if (flags & OPT_P)
		ft_strcmp("", word) == 0 ? ft_putf(1, "%s\n", value)
		: ft_putf(1, "%s%s\n", word, value);
	else if (flags & OPT_Q)
		ft_putf(1, "%s\n", value);
	else if (flags & OPT_R)
		flags & OPT_S ? ft_putf(1, "%s \"%s\" \n", value, word)
		: ft_putf(1, "%s %s \n", value, word);
	else 
		flags & OPT_S ? ft_putf(1, "%s (\"%s\") = %s\n", hash, word, value)
		: ft_putf(1, "%s (%s) = %s\n", hash, word, value);
	//free(value);
}
