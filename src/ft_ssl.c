#include <libft.h>

#include "ft_ssl.h"

static t_command	g_funcmap[] =
{
	{"sha256", hasher, sha256},
	{"md5", hasher, md5},
	{NULL, NULL, NULL},
};

int run(int const ac, char const **argv) {

    i32 i;

    i = -1;
    while (g_funcmap[++i].command != NULL)
    {
        if (!ft_strcmp(argv[1], g_funcmap[i].command))
            return (g_funcmap[i].func(ac, argv, g_funcmap[i].algo));
    }
    return (ft_retf(COMMAND_NOT_FOUND, INVALID_COMMAND, argv[1])); 
}

int main(int const ac, char const **argv) {
    if (ac && ac == 1)
        return (ft_retf(EXIT_FAILURE, USAGE));
    return (run(ac, argv));
}