#include "parsing.h"

char	*handle_backslash(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		str = str_join_char(str, **line);
		if (!str)
			free_all_exit(all, ENOMEM);
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
			free_all_exit(all, ENOMEM);
	}
	return (str);
}

char	*dollar_handler(char *str, t_all *all)
{
	char	*name;
	char	*value;
	// int 	start;

	// while (str[++(*i)] && str[(*i) != '$'])
	// 	;
	name = get_str(&str, all);
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
			free_all_exit(all, ENOMEM);
	}
	return (value);
}

void	check_and_handle_dollar(t_dlst *ptr_token, t_all *all)
{
	int		i;
	int		start;
	char	*value;
	char	*tmp;

	while (ptr_token)
	{
		i = 0;
		while (!(ptr_token->flag & ESCAPED_VARIABLE) && ptr_token->str[i])
		{
			if (ptr_token->str[i] == '$' && ptr_token->str[i + 1] == '?')
			{
				tmp = ptr_token->str;
				value = ft_itoa(all->exit_status);
				ptr_token->str = ft_str_replace(ptr_token->str, value, i, i + 1);
				check_memory_allocation_str(ptr_token->str);
				free(tmp);
				free(value);
				i++;
			}
			else if (ptr_token->str[i] == '$')
			{
				start = i;
				while (ptr_token->str[i + 1] && ptr_token->str[i + 1] != '$')
					i++;
				tmp = ptr_token->str;
				value = dollar_handler(ptr_token->str + start + 1, all);
				ptr_token->str = ft_str_replace(ptr_token->str, value, start, i);
				i = start + ft_strlen(value);
				check_memory_allocation_str(ptr_token->str);
				free(tmp);
				free(value);
			}
			else// if (ptr_token->str[i]))
				i++;
		}
		ptr_token = ptr_token->next;
	}
}

char	*get_variable_name(char **line, t_all *all)
{
	char	*name;

	name = ft_strjoin("$", get_str(line, all));
	if (!name)
		error_handler(NULL, ENOMEM);
	return (name);
}

char	*single_operator_handler(char **line, t_all *all)
{
	char	*str;

	str = str_join_char(NULL, **line);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, 1);
	(*line)++;
	return (str);
}

char	*double_operator_handler(char **line, t_all *all)
{
	char	*str;

	str = str_join_char(NULL, **line);
	str = ft_substr(*line, 0, 2);
	if (!str || !doubly_lst_append(&all->lst_token, doubly_lst_new(str, NONE)))
		free_all_exit(all, 1);
	str = str_join_char(NULL, '\0');
	if (!str)
		free_all_exit(all, 1);
	(*line)++;
	(*line)++;
	return (str);
}