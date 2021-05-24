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

char	*get_str_single_quotes(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_strchr("\'", **line))
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

char	*quote_handler(char **line, char *startpos_line, t_all *all)
{
	char	*str;

	str = NULL; // TEMP DELETE ME LATER!!!!
	if (!find_closing_quotes((*line + 1), **line))
	{
		doubly_lst_clear(&all->lst_token);
		error_handler("No closing quotes", 1);
		return (NULL);
	}
	if (**line == '\'' && ++(*line))
		str = get_str_single_quotes(line, startpos_line, all);
	// else if (*line == '\"')					will be done later!!!
	// 	tmp_str = double_quotes_handler();
	(*line)++;
	return (str);
}
