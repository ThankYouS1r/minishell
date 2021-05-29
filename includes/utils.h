#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define METACHARACTERS		"|;<>"
# define SUCCESS			0

enum	e_separators
{
	NONE,
	PIPE,
	SEMICOLON,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT,
	APPEND_REDIRECT_OUTPUT
};

typedef struct s_doubly_lst {
	char				*str;
	struct s_doubly_lst	*next;
	struct s_doubly_lst	*prev;
}				t_dlst;

typedef struct s_env
{
	size_t		size;
	char		**array;
}				t_env;

typedef struct s_all
{
	t_dlst		*lst_token;
	t_dlst		*shell_history;
	t_dlst		*ptr_history;
	t_dlst		*lst_env;
	int			exit_status;
}				t_all;

void			*ft_realloc(void *ptr, size_t size);
void			ft_crash(const char *str);
void			*ft_malloc(size_t size);
int				ft_iswhitespace(int c);
char			*str_join_char(char *str, char ch);
t_dlst			*doubly_lst_append(t_dlst **lst, t_dlst *new);
t_dlst			*doubly_lstlast(t_dlst *lst);
t_dlst			*doubly_lst_new(char *str);
void			doubly_lst_clear(t_dlst **lst);
int				free_all_exit(t_all *all, char *line, int error_code);
void			free_doble_array(char **array);
int				is_separator(char	*str);

#endif
