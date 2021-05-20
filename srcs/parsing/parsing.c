#include "parsing.h"


int	find_closing_quotes(char *line, char ch)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\\' && (line[i + 1] == '"' || line[i] == '\''))
			i++;
		else if (line[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

char	*get_token(const char *line, int *i, t_doubly_lst *token_lst, int quote)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (line[*i])
	{
		if (ft_iswhitespace(line[*i]))
			return (tmp_str);
		else if (is_spec_symbols(line[*i]) && !quote) // NEED TO BE REPAIRED
		{
			(*i)--;
			return (tmp_str);
		}
		tmp_str = str_join_char(tmp_str, line[*i]);
		if (!tmp_str)
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		(*i)++;
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
		if (line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '"'))
			i++;
		else if (line[i] == '\'' || line[i] == '"')
		{
			i++;
			if (find_closing_quotes(&line[i], line[i])) // Temp block, need to be changed
			{
				tmp_str = get_token(line, &i, token_lst, 1);
				if (tmp_str && !(doubly_lst_append(&token_lst, doubly_lst_new(tmp_str))))
				{
					doubly_lst_clear(&token_lst);
					error_handler(NULL, ENOMEM);
				}
			}
			else
				error_handler("No closing quotes", 1);

		}
		tmp_str = get_token(line, &i, token_lst, 0);
		if (tmp_str && !(doubly_lst_append(&token_lst, doubly_lst_new(tmp_str))))
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}

	}
	free (line);
	return (token_lst);
}
