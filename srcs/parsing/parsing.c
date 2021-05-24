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
		//	(*line)--;
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


void	merge_str_and_lst_append(char **merged_str, char*str, t_all *all, char *start_line, char *line)
{
	if (!*merged_str)
		*merged_str = ft_strdup(str);
	else
		*merged_str = ft_strjoin(*merged_str, str);
	if (!*merged_str)
	{
		free(str);
		free_all_exit(all, start_line, 1);
	}
	free(str);
	if (!(*line) || (ft_strchr("\'\"", (*line)) && (!(*line + 1))) || ft_iswhitespace(*line) || ft_strchr("|><;", (*line)))
	{
		if (!doubly_lst_append(&all->lst_token, doubly_lst_new(*merged_str)))
		{
			free(*merged_str);
			free_all_exit(all, start_line, 1);	
		}
		*merged_str = NULL;
	}
}

t_dlst	*parsing(t_all *all)
{
	char	*line;
	char	*start_line;
	char	*str;
	char	*merged_str;

	merged_str = NULL;
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
		merge_str_and_lst_append(&merged_str, str, all, start_line, line);
		// if (*line)
		// 	line++;
	}
	free(start_line);
	return (all->lst_token);
}
