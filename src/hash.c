#include "ft_ssl/hashing.h"

int read_stdin(char **line) {
	int		rd;
	char	buf[4096 + 1];
	char 	*cpy;
	
	*line = ft_strnew(1);
	while ((rd = read(STDIN_FILENO, buf, 4096)) != 0) {
		if (rd == ((buf[rd] = '\0') - 1))
			return (0);
		cpy = ft_strjoin(*line, buf);
		free(*line);
		*line = cpy;
	}
	return (1);
}

int hasher(int const ac, char const **argv, t_algo func) {
	t_hash hash;
	i32 i;
	char *input;

	input = NULL;
	if ((i = hash_parse(ac, argv, &hash, func)) <= 0)
		return (EXIT_FAILURE);
	if (i == ac && read_stdin(&input)) {
		func(input, hash.flags);
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
			if (!read_stdin(&input))
				return (-1);
			hash->flags & OPT_P ? func("", hash->flags) : func(input, hash->flags);
			hash->flags |= OPT_P;
			free(input);
		}
		else if (opt == 's' && (hash->flags |= OPT_S))
			func(g_optarg, hash->flags);
		else if (opt == 'q')
            hash->flags |= OPT_Q;
        else if (opt == 'r')
            hash->flags |= OPT_R;
		else
			return (-1);
	return (g_optind); 
}


