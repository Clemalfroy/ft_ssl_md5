#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_ssl/hashing.h"

#define USAGE "usage: ./ft_ssl command [command opts] [command args]\n"

#define COMMAND_NOT_FOUND -1 
#define INVALID_COMMAND "Error: Command not found: %s\n" 

typedef int (*t_algo)(const char *, short);
typedef int (* t_commands)(int const, char const **, t_algo); 

typedef struct  s_command {
    const char *command;
    t_commands func;
    t_algo  algo;
}               t_command;

#endif