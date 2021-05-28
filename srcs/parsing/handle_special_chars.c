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
		if (ft_strchr(SRECIAL_CHARS, (*line)[1]))
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
	value = getenv_from_array((const char **)all->env.array, name);
	if (!value)
	{
		value = ft_strdup("");
		if (!value)
		{
			free(name);
			free_all_exit(all, startpos_line, ENOMEM);
		}
	}
	free(name);
	return (value);
}
