#include "parsing.h"

int	find_closing_quotes(const char *line, char quote)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && (line[i + 1] == '"' || line[i] == '\''))
			i++;
		else if (line[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

char	*quote_handler(char **line, t_dlst *token_lst)
{
	char	*str;

	if (!find_closing_quotes((*line + 1), **line))
	{
		doubly_lst_clear(&token_lst);
		token_lst = NULL;
		error_handler("No closing quotes", 1);
		return (NULL);
	}
	if (**line == '\'' && ++(*line))
		str = get_str(line, token_lst, "\'", CLOSING_QUOTE);
	// else if (*line == '\"')					will be done later!!!
	// 	tmp_str = double_quotes_handler();
	return (str);
}
