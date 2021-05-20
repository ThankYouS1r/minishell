#include "utils.h"

t_doubly_lst	*doubly_lstlast(t_doubly_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
