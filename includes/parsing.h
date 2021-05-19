#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct	s_parser
{
	char		*str;
	int			count;
}				t_parser;

struct termios 	ft_init_settings(void);
int				ft_parse_args(int ac, char **av, struct termios saved_attributes);

#endif