#include "parsing.h"

char	*double_quotes_manager(t_line *l, t_all *all)
{
	char	*str;

	if (ft_strchr("\"", *l->line))
	{
		str = ft_strdup("");
		if (!str)
			free_all_exit(all, l->start_line, ENOMEM);
		return (str);
	}
	if (*l->line == '\\' && ++(l->line))
		str = handle_backslash(&l->line, l->start_line, all);
	else if (*l->line == '\'')
		str = quote_handler(l, all);
	else if (*l->line == '$' && ++(l->line))
		str = dollar_handler(&l->line, l->start_line, all);
	else if (*l->line == '|' || *l->line == ';' || *l->line == '<'
		|| *l->line == '>' || ft_iswhitespace(*l->line))
	{
		str = str_join_char(NULL, *l->line);
		l->line++;
	}
	else
		str = get_str(&l->line, l->start_line, all);
	return (str);
}

char	*join_str_dquotes(char	*merged_str, char *str, t_all *all, char *line)
{
	if (!merged_str)
		merged_str = ft_strdup(str);
	else
		merged_str = ft_strjoin(merged_str, str);
	if (!merged_str)
	{
		free(str);
		free_all_exit(all, line, 1);
	}
	free(str);
	if (!(*merged_str))
	{
		free(merged_str);
		merged_str = NULL;
	}
	return (merged_str);
}

char	*double_quotes_handler(t_line *l, t_all *all)
{
	char	*str;
	char	*merged_str;

	merged_str = NULL;
	str = NULL;
	while (*l->line != '\"')
	{
		str = double_quotes_manager(l, all);
		if (!str)
		{
			free (l->start_line);
			return (NULL);
		}
		merged_str = join_str_dquotes(merged_str, str, all, l->start_line);
	}
	if (!str)
	{
		merged_str = ft_strdup("");
		if (!merged_str)
			free_all_exit(all, l->start_line, ENOMEM);
	}
	(l->line)++;
	return (merged_str);
}
