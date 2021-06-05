#include "utils.h"

t_dlst	*doubly_lst_new(char *str)
{
	t_dlst	*new;

	new = (t_dlst *)malloc(sizeof(t_dlst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->str = str;
	return (new);
}
