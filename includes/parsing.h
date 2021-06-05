#ifndef PARSING_H
# define PARSING_H

# include "error_handlers.h"
# include "minishell.h"
# include "environment.h"

# define ESCAPE_CHAR			0b00000001
# define CLOSING_QUOTE			0b00000010
# define CLOSING_DOUBLE_QUOTE	0b00000100
# define SPEC_SYMBOLS			0b00001000

# define SRECIAL_CHARS			"$&;|<>\'\\\""
# define DQUOTES_EXCEPTION		"\\$`\""

typedef struct s_line {
	char	*line;
	char	*start_line;
	char	*str;
	char	*merged_str;
}				t_line;

int			read_line(int fd, char **line);
t_dlst		*parsing(t_all *all);
char		*quote_handler(t_line *l, t_all *all);
char		*handle_backslash(char **line, char *startpos_line, t_all *all);
char		*dollar_handler(char **line, char *startpos_line, t_all *all);
char		*get_str(char **line, char *startpos_line, t_all *all);
void		merge_str_and_lst_append(t_line *l, t_all *all);
char		*double_quotes_handler(t_line *l, t_all *all);
void 		add_history_to_lst(char *str, t_dlst **head, t_dlst **p_history);

#endif
