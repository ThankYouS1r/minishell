#include "utils.h"

t_doubly_lst	*doubly_lst_append(t_doubly_lst **lst, t_doubly_lst *new)
{
	t_doubly_lst	*tmp;

	if (!new)
		return (NULL);
	tmp = *lst;
	if (!*lst)
		(*lst) = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*lst);
}
