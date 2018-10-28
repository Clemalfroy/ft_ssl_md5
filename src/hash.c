/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <cmalfroy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:30 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/06 12:00:10 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl/hashing.h"
#include <stdio.h>

int			string_hash(const char *str, t_hash *hash, t_algo func)
{
	hash->flags |= OPT_S;
	if (!func(str, hash))
		return (0);
	hash->flags &= ~OPT_S;
	return (1);
}

int			hasher(int const ac, char const **argv, t_algo func)
{
	t_hash	hash;
	int32_t	i;
	char	*input;

	input = NULL;
	hash.flags = 0;
	if ((i = hash_parse(ac, argv, &hash, func)) <= 0)
		return (EXIT_FAILURE);
	if (i == ac && (ac <= 2 || (hash.flags & OPT_Q &&
	!(hash.flags & OPT_DONE))))
	{
		ft_read_all(STDIN_FILENO, &input);
		hash.flags |= OPT_DONE;
		hash.flags |= OPT_Q;
		string_hash(input, &hash, func);
		free(input);
	}
	hash.flags &= ~OPT_S;
	while (i++ < ac)
		func(argv[i - 1], &hash);
	return (EXIT_SUCCESS);
}

int			hash_parse(int const ac, char const **argv, t_hash *hash,
	t_algo func)
{
	int		opt;
	char	*input;

	input = NULL;
	g_optind = 2;
	while ((opt = ft_getopt(ac, argv, "pqrs:")) != -1)
		if (opt == 'p')
		{
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

void		print_digest(uint32_t *digest, t_hash *hashopt)
{
	uint32_t	i;
	uint32_t	tmp;

	i = 0;
	while (i < hashopt->size / 4)
	{
		tmp = digest[i];
		if (hashopt->swap_endian)
			tmp = swap_int32(tmp);
		printf("%8.8x", tmp);
		i++;
	}
}

void		display_hash(char const *hash, uint32_t *digest, char const *word,
t_hash *hashopt)
{
	if (hashopt->flags & OPT_P)
	{
		ft_strcmp("", word) == 0 ? 0 : printf("%s", word);
		print_digest(digest, hashopt);
	}
	else if (hashopt->flags & OPT_Q)
		print_digest(digest, hashopt);
	else if (hashopt->flags & OPT_R)
	{
		print_digest(digest, hashopt);
		hashopt->flags & OPT_S ? printf(" \"%s\"", word)
		: printf(" %s", word);
	}
	else
	{
		hashopt->flags & OPT_S ? printf("%s (\"%s\") = ", hash, word)
		: printf("%s (%s) = ", hash, word);
		print_digest(digest, hashopt);
	}
	printf("\n");
	free(digest);
}

uint32_t	*hash_file(const char *str, t_hashalgo func)
{
	char		*content;
	uint32_t	*digest;
	int			fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_putf(STDERR_FILENO, "%s: %e\n", str, errno);
		return (NULL);
	}
	content = NULL;
	if (!ft_read_all(fd, &content))
		return (NULL);
	digest = func(content);
	free(content);
	return (digest);
}
