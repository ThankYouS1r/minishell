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

char	*get_variable_name(char **line, t_all *all)
{
	char	*str;

	str = NULL;
	while (**line)
	{
		if (ft_iswhitespace(**line))
			break ;
		else if (**line != '_' && !ft_isalnum(**line))
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


char	*dollar_handler(char **str, t_all *all)
{
	char	*name;
	char	*value;

	if (**str == '?')
	{
		value = ft_itoa(all->exit_status);
		if (!value)
			free_all_exit(all, ENOMEM);
		(*str)++;
		return (value);
	}
	name = get_variable_name(str, all);
	if (last_token(all->lst_token) == HERE_DOCUMENT || name[0] == '\0')
	{
		value = ft_strjoin("$", name);
		if (!value)
			error_handler(NULL, ENOMEM);
		free(name);
		return (value);
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

// void	check_and_handle_dollar(t_dlst *ptr_token, t_all *all)
// {
// 	int		i;
// 	int		start;
// 	char	*value;
// 	char	*tmp;

// 	while (ptr_token && is_separator(ptr_token) != SEMICOLON)
// 	{
// 		i = 0;
// 		while (ptr_token->str[i])
// 		{
// 			if (ptr_token->str[i] == 6)
// 				ptr_token->str[i++] = '$';
// 			else if (ptr_token->str[i] == '$' && ptr_token->str[i + 1] == '?')
// 			{
// 				tmp = ptr_token->str;
// 				value = ft_itoa(all->exit_status);
// 				ptr_token->str = ft_str_replace(ptr_token->str, value, i, i + 1);
// 				check_memory_allocation_str(ptr_token->str);
// 				free(tmp);
// 				free(value);
// 				i++;
// 			}
// 			else if (ptr_token->str[i] == '$')
// 			{
// 				start = i;
// 				while (ptr_token->str[i + 1]
// 					&& !ft_iswhitespace(ptr_token->str[i + 1])
// 					&& !ft_strchr(SPECIAL_CHARS, ptr_token->str[i + 1]))
// 					i++;
// 				tmp = ptr_token->str;
// 				value = dollar_handler(ptr_token->str + start + 1, all);
// 				ptr_token->str = ft_str_replace(ptr_token->str, value, start, i);
// 				i = start + ft_strlen(value);
// 				check_memory_allocation_str(ptr_token->str);
// 				free(tmp);
// 				free(value);
// 			}
// 			else// if ((*ptr_token)->str[i]))
// 				i++;
// 		}
// 		ptr_token = ptr_token->next;
// 	}
// }

// char	*get_variable_name(char **line, t_all *all)
// {
// 	char	*name;
// 	char	*str;

// 	str = get_str(line, all);
// 	name = ft_strjoin("$", str);
// 	if (!name)
// 		error_handler(NULL, ENOMEM);
// 	free(str);
// 	return (name);
// }

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