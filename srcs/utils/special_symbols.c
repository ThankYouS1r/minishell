#include "utils.h"

int	is_separator(t_dlst *ptr_token)
{
	if (ptr_token->str[0] == '|' && ptr_token->str[1] == '\0')
		return (PIPE);
	// else if (ptr_token->str[0] == '|' && ptr_token->str[1] == '\0' &&
	// 	(!ptr_token->next || is_separator(ptr_token->next)))
	// 	return (LAST_PIPE);
	else if (ptr_token->str[0] == ';' && ptr_token->str[1] == '\0')
		return (SEMICOLON);
	else if (ptr_token->str[0] == '<' && ptr_token->str[1] == '\0')
		return (REDIRECT_INPUT);
	else if (ptr_token->str[0] == '>' && ptr_token->str[1] == '\0')
		return (REDIRECT_OUTPUT);
	else if (ptr_token->str[0] == '>' &&
		ptr_token->str[1] == '>' && ptr_token->str[2] == '\0')
		return (APPEND_REDIRECT_OUTPUT);
	return (NONE);
}

int	next_operator(t_dlst *ptr_token)
{
	while (ptr_token->next && !is_separator(ptr_token))
		ptr_token = ptr_token->next;
	return (is_separator(ptr_token));
}

int	prev_operator(t_dlst *ptr_token)
{
	if (!ptr_token || !ptr_token->prev)
		return (0);
	while (ptr_token->prev && !is_separator(ptr_token))
		ptr_token = ptr_token->prev;
	return (is_separator(ptr_token));
}