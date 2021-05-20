#include "parsing.h"


int	find_closing_quotes(char *line, char ch)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && (line[i] == '"' || line[i] == '\''))
			i++;
		else if (line[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char	*get_token(const char *line, int *i, t_doubly_lst *token_lst)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (line[*i])
	{
		if (is_spec_symbols(line[*i]) || ft_iswhitespace(line[*i]))
			return (tmp_str);
		tmp_str = str_join_char(tmp_str, line[*i]);
		if (!tmp_str)
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
	}
	return (tmp_str);
}

t_doubly_lst	*parsing(t_doubly_lst	*token_lst)
{
	char	*line;
	int		i;
	char	*tmp_str;

	token_lst = NULL;
	line = read_line();
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'' || (line[i] == '\\' && line[i + 1] == '"'))
			i++;
		else if (line[i] == '\'' || line[i] == '"')
			find_closing_quotes(line + i, line[i]);
		tmp_str = get_token(line + i, &i, token_lst);
		if (!(doubly_lst_append(&token_lst, doubly_lst_new(tmp_str))))
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		// else if (ft_iswhitespace(line[i]))
		// 	++i;
	}
	free (line);
	return (token_lst);
}
