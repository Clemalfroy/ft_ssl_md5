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

#include <libft.h>
#include "ft_ssl.h"

static t_command	g_funcmap[] =
{
	{"sha256", hasher, sha256},
	{"md5", hasher, md5},
	{NULL, NULL, NULL},
};

int		run(int const ac, char const **argv)
{
	int	i;

	i = -1;
	while (g_funcmap[++i].command != NULL)
	{
		if (!ft_strcmp(argv[1], g_funcmap[i].command))
			return (g_funcmap[i].func(ac, argv, g_funcmap[i].algo));
	}
	return (ft_retf(COMMAND_NOT_FOUND, INVALID_COMMAND, argv[1]));
}

int		main(int const ac, char const **argv)
{
	if (ac && ac == 1)
		return (ft_retf(EXIT_FAILURE, USAGE));
	return (run(ac, argv));
}
