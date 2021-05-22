#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

typedef struct s_doubly_lst {
	char				*str;
	struct s_doubly_lst	*next;
	struct s_doubly_lst	*prev;
}				t_dlst;

char			**duplicate_string_array(const char *str_array[], size_t size);
void			*ft_realloc(void *ptr, size_t size);
void			ft_crash(const char *str);
void			*ft_malloc(size_t size);
int				ft_iswhitespace(int c);
int				is_spec_symbols(char ch);
char			*str_join_char(char *str, char ch);
t_dlst			*doubly_lst_append(t_dlst **lst, t_dlst *new);
t_dlst			*doubly_lstlast(t_dlst *lst);
t_dlst			*doubly_lst_new(char *str);
void			doubly_lst_clear(t_dlst **lst);

#endif
