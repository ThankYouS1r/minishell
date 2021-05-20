#include "parsing.h"

int	is_spec_symbols(char ch)
{
	if (ch == '"' || ch == 27 || ch == '/' || ch == '$')
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
	if (ch == 27)
		return (1);
	return (0);
}
int	is_slash(char ch)
{
	if (ch == '/')
		return (1);
	return (0);
}
int	is_dollar(char ch)
{
	if (ch == '$')
		return (1);
	return (0);
}