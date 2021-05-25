#ifndef PARSING_H
# define PARSING_H

# include "error_handlers.h"
# include "utils.h"
# include "minishell.h"
# include "environment.h"

# define ESCAPE_CHAR			0b00000001
# define CLOSING_QUOTE			0b00000010
# define CLOSING_DOUBLE_QUOTE	0b00000100
# define SPEC_SYMBOLS			0b00001000

# define SRECIAL_CHARS			"$&;|<>\'\\\""

typedef struct s_line {
	char	*line;
	char	*start_line;
	char	*str;
	char	*merged_str;
}				t_line;

char		*read_line(void);
int			is_double_quotes(char ch);
int			is_single_quotes(char ch);
int			is_backslash(char ch);
int			is_dollar(char ch);
t_dlst		*parsing(t_all *all);
char		*quote_handler(t_line *l, t_all *all);
char		*handle_backslash(char **line, char *startpos_line, t_all *all);
char		*dollar_handler(char **line, char *startpos_line, t_all *all);
char		*get_str(char **line, char *startpos_line, t_all *all);
void		merge_str_and_lst_append(t_line *l, t_all *all);
char		*double_quotes_handler(t_line *l, t_all *all);

#endif
