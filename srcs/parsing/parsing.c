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

char	*get_token(char **line, t_doubly_lst *token_lst, char *spec_symbols, int check_first_symbol)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			return (tmp_str);
		else if (!check_first_symbol && ft_strchr("$|<>\'\\\"", **line))
			check_first_symbol = 1;
		else if (ft_strchr(spec_symbols, **line))
		{
			if (**line != '\'' || line[0][1] != '\0')
				(*line)--;
			return (tmp_str);
		}
		tmp_str = str_join_char(tmp_str, **line);
		if (!tmp_str)
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		(*line)++;
	}
	return (tmp_str);
}

t_doubly_lst	*parsing(t_doubly_lst	*token_lst)
{
	char	*line;
	char	*old_line;
	char	*tmp_str;

	token_lst = NULL;
	line = read_line();
	old_line = line;
	while (*line)
	{
		if (*line == '\\' && ++line)
			tmp_str = get_token(&line, token_lst, "$|<>\'\\\"", 0);
		else if (*line == '\'' || *line == '"')
		{
			if (!find_closing_quotes((line + 1), *line))
			{
				doubly_lst_clear(&token_lst);
				token_lst = NULL;
				error_handler("No closing quotes", 1);
				return (token_lst);
			}
			if (*line == '\'' && ++line)
				tmp_str = get_token(&line, token_lst, "\'", 1);
			// else if (*line == '\"')					will be done later!!!
			// 	tmp_str = double_quotes_handler();
		}
		else
			tmp_str = get_token(&line, token_lst, "$|<>\'\\\"", 1);
		if (tmp_str && !(doubly_lst_append(&token_lst, doubly_lst_new(tmp_str))))
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		if (*line)
			line++;
	}
	free (old_line);
	return (token_lst);
}
