#include "utils.h"

int	is_spec_symbols(char ch)
{
	if (ch == '"' || ch == '\'' || ch == '\\' || ch == '$')
		return (1);
	return (0);
}

int	is_double_quotes(char ch)
{
	if (ch == '"')
		return (1);
	return (0);
}

int	is_single_quotes(char ch)
{
	if (ch == '\'')
		return (1);
	return (0);
}
int	is_backslash(char ch)
{
	if (ch == '\\')
		return (1);
	return (0);
}
int	is_dollar(char ch)
{
	if (ch == '$')
		return (1);
	return (0);
}
