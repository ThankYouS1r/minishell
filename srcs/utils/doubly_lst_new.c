#include "utils.h"

t_doubly_lst	*doubly_lst_new(char *str)
{
	t_doubly_lst	*new;

	new = (t_doubly_lst *)malloc(sizeof(t_doubly_lst));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->str = str;
	return (new);
}
