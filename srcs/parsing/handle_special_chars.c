#include "parsing.h"

char	*handle_backslash(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, startpos_line, ENOMEM);
		if (ft_strchr(SPECIAL_CHARS, (*line)[1]))
		{
			(*line)++;
			return (str);
		}
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
	char	*name;
	char	*value;

	if (**line == '?')
	{
		value = ft_itoa(all->exit_status);
		if (!value)
			free_all_exit(all, startpos_line, ENOMEM);
		(*line)++;
		return (value);
	}
	name = get_str(line, startpos_line, all);
	if (last_token(all->lst_token) == HERE_DOCUMENT || name[0] == '\0')
	{
		name = ft_strjoin("$", name);
		if (!name)
			error_handler(NULL, ENOMEM);
		return (name);
	}

	value = getenv_from_lst(all->env, name);
	free(name);
	if (!value)
	{
		value = ft_strdup("");
		if (!value)
			free_all_exit(all, startpos_line, ENOMEM);
	}
	return (value);
}

char	*single_operator_handler(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = str_join_char(NULL, **line);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, startpos_line, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, startpos_line, 1);
	(*line)++;
	return (str);
}

char	*double_operator_handler(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = str_join_char(NULL, **line);
	str = ft_substr(*line, 0, 2);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, startpos_line, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, startpos_line, 1);
	(*line)++;
	(*line)++;
	return (str);
}