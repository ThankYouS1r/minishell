#include "utils.h"

int	is_separator(char	*str)
{
	if ((str[0] == '|') && str[1] == '\0')
		return (PIPE);
	else if ((str[0] == ';') && str[1] == '\0')
		return (SEMICOLON);
	else if ((str[0] == '<') && str[1] == '\0')
		return (REDIRECT_INPUT);
	else if ((str[0] == '>') && str[1] == '\0')
		return (REDIRECT_OUTPUT);
	else if ((str[0] == '>') && str[1] == '>' && str[2] == '\0')
		return (APPEND_REDIRECT_OUTPUT);
	return (NONE);
}
