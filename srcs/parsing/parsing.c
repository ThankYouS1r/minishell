#include "parsing.h"

char	*get_str(char **line, t_dlst *token_lst, char *stop_symb, int flag_char)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			return (str);
		else if (flag_char & ESCAPE_CHAR)
			flag_char &= ~ESCAPE_CHAR;
		else if (ft_strchr(stop_symb, **line))
		{
			if (flag_char & SPEC_SYMBOLS)
				(*line)--;
			return (str);
		}
		str = str_join_char(str, **line);
		if (!str)
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		(*line)++;
	}
	return (str);
}

char	*dollar_handler(char **line, t_dlst *token_lst, t_env *env)
{
	char	*str;
	char	*tmp_str;

	str = get_str(line, token_lst, "$&;|<>\'\\\"", SPEC_SYMBOLS);
	tmp_str = str;
	str = getenv_from_array((const char **)env->array, str);
	free(tmp_str);
	return (str);
}

char	*parse_line(char **line, char *tmp_line, t_all *all)
{
	char	*str;

	if (**line == '\\' && ++(*line))
		str = handle_backslash(line--, tmp_line, all);
	else if (**line == '\'' || **line == '"')
		str = quote_handler(line--, tmp_line, all);
	else if (**line == '$' && ++(*line))
		str = dollar_handler(line, all->lst_token, &all->env);
	else if (**line == '|' || **line == ';' || **line == '<'
		|| **line == '>')
		str = str_join_char(NULL, **line);
	else
		str = get_str(line, all->lst_token, "$&;|<>\'\\\"", SPEC_SYMBOLS);
	return (str);
}

t_dlst	*parsing(t_all *all)
{
	char	*line;
	char	*start_line;
	char	*str;

	line = read_line();
	if (!line)
		free_all_exit(all, NULL, 1);
	start_line = line;
	while (*line)
	{
		str = parse_line(&line, start_line, all);
		if (!str)
		{
			free (start_line);
			return (NULL);
		}
		if (str && !(doubly_lst_append(&all->lst_token, doubly_lst_new(str))))
			free_all_exit(all, start_line, ENOMEM);
		if (*line)
			line++;
	}
	free(start_line);
	return (all->lst_token);
}
