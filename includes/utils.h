/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:59:11 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/20 12:42:07 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

typedef struct s_doubly_lst {
	char				*str;
	struct s_doubly_lst	*next;
	struct s_doubly_lst	*prev;
}				t_doubly_lst;

char			**duplicate_string_array(const char *str_array[], size_t size);
void			*ft_realloc(void *ptr, size_t size);
void			ft_crash(const char *str);
void			*ft_malloc(size_t size);
int				ft_iswhitespace(int c);
char			*str_join_char(char *str, char ch);
t_doubly_lst	*doubly_lst_append(t_doubly_lst **lst, t_doubly_lst *new);
t_doubly_lst	*doubly_lstlast(t_doubly_lst *lst);
t_doubly_lst	*doubly_lst_new(char *str);
void			doubly_lst_clear(t_doubly_lst **lst);


#endif
