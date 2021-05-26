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
			break ;
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

char	*parse_line(t_line *l, t_all *all)
{
	char	*str;

	while (ft_iswhitespace(*l->line))
		++(l->line);
	if (*l->line == '\\' && ++(l->line))
		str = handle_backslash(&l->line, l->start_line, all);
	else if (*l->line == '\'' || *l->line == '"')
		str = quote_handler(l, all);
	else if (*l->line == '$' && ++(l->line))
		str = dollar_handler(&l->line, l->start_line, all);
	else if (*l->line == '|' || *l->line == ';' || *l->line == '<'
		|| *l->line == '>' || *l->line == '&')
	{
		str = str_join_char(NULL, *l->line);
		(l->line)++;
	}
	else
		str = get_str(&l->line, l->start_line, all);
	return (str);
}

void	merge_str_and_lst_append(t_line *l, t_all *all)
{
	if (!l->merged_str)
		l->merged_str = ft_strdup(l->str);
	else
		l->merged_str = ft_strjoin(l->merged_str, l->str);
	if (!l->merged_str)
	{
		free(l->str);
		free_all_exit(all, l->start_line, 1);
	}
	free(l->str);
	if (!(*l->merged_str))
	{
		free(l->merged_str);
		l->merged_str = NULL;
	}
	else if (!*l->line || (ft_strchr("\'\"", *l->line) && (!(*(l->line + 1))))
		|| ft_iswhitespace(*l->line) || ft_strchr("|><;", (*l->line)))
	{
		if (!doubly_lst_append(&all->lst_token, doubly_lst_new(l->merged_str)))
		{
			free(l->merged_str);
			free_all_exit(all, l->start_line, 1);
		}
		l->merged_str = NULL;
	}
}

t_dlst	*parsing(t_all *all)
{
	t_line	line;

	line.merged_str = NULL;
	line.line = read_line();
	if (!line.line)
		free_all_exit(all, NULL, 1);
	line.start_line = line.line;
	while (*line.line)
	{
		line.str = parse_line(&line, all);
		if (!line.str)
		{
			free (line.start_line);
			return (NULL);
		}
		merge_str_and_lst_append(&line, all);
	}
	free(line.start_line);
	return (all->lst_token);
}
