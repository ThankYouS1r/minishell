#include "parsing.h"

char	*get_str(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if ((ft_strchr(SPECIAL_CHARS, **line)))
			break ;
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, ENOMEM);
		(*line)++;
	}
	if (!str)
	{
		str = ft_strdup("");
		if (!str)
			free_all_exit(all, ENOMEM);
	}
	return (str);
}

char	*parse_line(t_line *l, t_all *all, int *escaped_char)
{
	t_str	s;

	while (ft_iswhitespace(*l->line))
		++(l->line);
	s.escaped_char = NONE;
	if ((*l->line == '\\')
		|| (*l->line == '\'' || *l->line == '"'))
		s.escaped_char |= ESCAPED_CHAR;
	if ((*l->line == '\\') || (*l->line == '\'')) 
		s.escaped_char |= ESCAPED_VARIABLE;
	if (*l->line == '\\' && ++(l->line))
		s.str = handle_backslash(&l->line, all);
	else if (*l->line == '\'' || *l->line == '"')
		s.str = quote_handler(l, all);
	else if (*l->line == '$' && ++(l->line))
		s.str = get_variable_name(&l->line, all);
	else if ((*l->line == '>' && l->line[1] == '>')
		|| (*l->line == '<' && l->line[1] == '<'))
		s.str = double_operator_handler(&l->line, all);
	else if (*l->line == '|' || *l->line == ';' || *l->line == '<'
		|| *l->line == '>' || *l->line == '&')
		s.str = (single_operator_handler(&l->line, all));
	else
		s.str = get_str(&l->line, all);
	*escaped_char = s.escaped_char;
	return (s.str);
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
		free_all_exit(all, 1);
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
		if (!doubly_lst_append(&all->lst_token, doubly_lst_new(l->merged_str, l->escaped_char)))
		{
			free(l->merged_str);
			free_all_exit(all, 1);
		}
		l->merged_str = NULL;
	}
}

t_dlst	*parsing(t_all *all)
{
	t_line	line;

	line.merged_str = NULL;
	line.line = ft_strdup(all->line);
	//read_line(STDIN_FILENO, &line.line);
	if (!line.line)
		free_all_exit(all, 1);
	// line.start_line = line.line;
	add_history_to_lst(line.line, &all->shell_history, &all->ptr_history);
	while (*line.line)
	{
		line.str = parse_line(&line, all, &line.escaped_char);
		if (!line.str)
			return (NULL);
		merge_str_and_lst_append(&line, all);
		// if (!ft_strcmp(all->lst_token->str, ";") || !(*line.line))
		// {
		// 	executor_loop(all);
		// 	doubly_lst_clear(&all->lst_token);
		// }
	}
	return (all->lst_token);
}
