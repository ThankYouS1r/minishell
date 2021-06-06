#include "utils.h"

void	go_to_end_or_separator(t_dlst **ptr_token)
{
	while (*ptr_token && !is_separator(*ptr_token))
			*ptr_token = (*ptr_token)->next;
}
