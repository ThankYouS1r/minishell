#ifndef PARSING_H
# define PARSING_H

# include "error_handlers.h"
# include "utils.h"
# include "minishell.h"

char			*read_line(void);
int				is_double_quotes(char ch);
int				is_single_quotes(char ch);
int				is_backslash(char ch);
int				is_dollar(char ch);
t_doubly_lst	*parsing();

#endif
