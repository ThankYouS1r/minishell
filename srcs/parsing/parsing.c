#include "parsing.h"

char	*get_str(char **line, t_dlst *token_lst, char *stop_symb, int flag_char)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			return (str);
		else if ((flag_char & ESCAPE_CHAR) && ft_strchr("$|<>\'\\\"", **line))
			flag_char &= ~ESCAPE_CHAR;
		else if (ft_strchr(stop_symb, **line))
		{
			if (**line == '\'' && (flag_char & SPEC_SYMBOLS))
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

	str = get_str(line, token_lst, "\'", SPEC_SYMBOLS);
	tmp_str = str;
	str = getenv_from_array((const char **)env->array, str);
	free(tmp_str);
	return (str);
}

char	*parse_line(char **line, char *tmp_line, t_dlst *token_lst, t_env *env)
{
	char	*str;

	if (**line == '\\' && ++(*line))
		str = get_str(line, token_lst, "$&;|<>\'\\\"", ESCAPE_CHAR
				| SPEC_SYMBOLS);
	else if (**line == '\'' || **line == '"')
	{
		str = quote_handler(line, token_lst);
		if (!str)
		{
			free (tmp_line);
			return (NULL);
		}
	}
	else if (**line == '$' && ++(*line))
		str = dollar_handler(line, token_lst, env);
	else
		str = get_str(line, token_lst, "$&;|<>\'\\\"", SPEC_SYMBOLS);
	return (str);
}

t_dlst	*parsing(t_dlst *token_lst, t_env *env)
{
	char	*line;
	char	*start_line;
	char	*str;

	line = read_line();
	start_line = line;
	while (*line)
	{
		str = parse_line(&line, start_line, token_lst, env);
		if (!str)
			return (NULL);
		if (str && !(doubly_lst_append(&token_lst, doubly_lst_new(str))))
		{
			doubly_lst_clear(&token_lst);
			error_handler(NULL, ENOMEM);
		}
		if (*line)
			line++;
	}
	free (start_line);
	return (token_lst);
}
