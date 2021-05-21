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

char	*get_from_quotes(const char *line, char quote, int *i)
{
	int 	start; 
	int		j;
	char	*str;

	
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		++(*i);
	str = (char *)malloc(*i - start + 1);
	if (!str)
		return (NULL);
	str[*i - start] = '\0';
	j = -1;
	while (start < *i)
		str[++j] = line[start++];
	++(*i);
	return (str);
}

char	*get_token(const char *line, int *i, t_doubly_lst *token_lst, int print_quote)
{
	char	*tmp_str;

	tmp_str = NULL;
	while (line[*i])
	{
		if (ft_iswhitespace(line[*i]))
			return (tmp_str);
		else if (is_spec_symbols(line[*i]) && !print_quote) // NEED TO BE REPAIRED
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
	int 	print_quote;

	token_lst = NULL;
	line = read_line();
	i = -1;
	while (line[++i])
	{
		print_quote = 0;
		if (line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '"'))	
			print_quote = ++i;
		else if (line[i] == '\'' || line[i] == '"')
		{
			if (find_closing_quotes(&line[i + 1], line[i])) // Temp block, need to be changed
			{
				if (!(doubly_lst_append(&token_lst, doubly_lst_new(get_from_quotes(line, line[i], &i)))))
				{
					doubly_lst_clear(&token_lst);
					error_handler(NULL, ENOMEM);
				}
			}
			else
			{
				doubly_lst_clear(&token_lst);
				token_lst = NULL;
				error_handler("No closing quotes", 1);
				return (token_lst);
			}
		}
			tmp_str = get_token(line, &i, token_lst, print_quote);
			if (tmp_str && !(doubly_lst_append(&token_lst, doubly_lst_new(tmp_str))))
			{
				doubly_lst_clear(&token_lst);
				error_handler(NULL, ENOMEM);
			}
	}
	free (line);
	return (token_lst);
}
