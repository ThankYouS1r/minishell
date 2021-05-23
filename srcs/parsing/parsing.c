#include "parsing.h"

char	*get_str(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if (ft_strchr(SRECIAL_CHARS, **line))
		{
			(*line)--;
			break ;
		}
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, startpos_line, ENOMEM);
		(*line)++;
	}
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			free_all_exit(all, startpos_line, ENOMEM);
	}
	return (str);
}

char	*dollar_handler(char **line, char *startpos_line, t_all *all)
{
	char	*str;
	char	*tmp_str;

	str = get_str(line, startpos_line, all);
	tmp_str = str;
	str = getenv_from_array((const char **)all->env.array, str);
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
		{
			free(tmp_str);
			free_all_exit(all, startpos_line, ENOMEM);
		}
	}
	free(tmp_str);
	return (str);
}

char	*parse_line(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	while (ft_iswhitespace(**line))
		++(*line);
	if (**line == '\\' && ++(*line))
		str = handle_backslash(line, startpos_line, all);
	else if (**line == '\'' || **line == '"')
		str = quote_handler(line, startpos_line, all);
	else if (**line == '$' && ++(*line))
		str = dollar_handler(line, startpos_line, all);
	else if (**line == '|' || **line == ';' || **line == '<'
		|| **line == '>')
		str = str_join_char(NULL, **line);
	else
		str = get_str(line, startpos_line, all);
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
