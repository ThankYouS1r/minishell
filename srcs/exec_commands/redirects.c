#include "exec_commands.h"


int	open_fd_input_redirect(t_all *all, t_dlst **ptr_token)
{
	int		fd;
	t_dlst	*tmp;

	tmp = *ptr_token;
	go_to_end_or_separator(&tmp);
	if (tmp->next)
	{
		if (all->fd_in != STDIN_FILENO)
			close(all->fd_in);
		fd = open(tmp->next->str, O_RDONLY, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDIN_FILENO);
		}
		return (fd);
	}
	return (all->fd_in);
}

int     open_fd_output_redirect(t_all *all, t_dlst **ptr_token)
{
    int		fd;
	t_dlst	*tmp;

	fd = STDOUT_FILENO;
    tmp = *ptr_token;
    go_to_end_or_separator(&tmp);
    if (tmp->next)
	{
		if (all->fd_out != STDOUT_FILENO)
			close(all->fd_out);
        if (all->next_operator == REDIRECT_OUTPUT)
		    fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        else if (all->next_operator == APPEND_REDIRECT_OUTPUT)
		    fd = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDOUT_FILENO);
		}
		return (fd);
	}
	return (all->fd_in);
}
char *get_variable_value(char *line, t_all *all, int *i)
{
	char	*value;
	int		start;
	char	*sub_str;

	start = ++(*i);
	if (line[*i] == '?')
	{
		value = ft_itoa(all->exit_status);
		if (!value)
			error_handler(NULL, ENOMEM);
		return (value);
	}
	while (line[*i] && !ft_strchr(SPECIAL_CHARS, line[*i]))
		(*i)++;
	if (*i - start == 0)
	{
		value = ft_strdup("$");
		if (!value)
			error_handler(NULL, ENOMEM);
	}
	else
	{
		sub_str = ft_substr(line, start, *i - start);
		if (!sub_str)
			error_handler(NULL, ENOMEM);
		value = getenv_from_lst(all->env, sub_str);
		free(sub_str);
		if (!value)
		{
			value = ft_strdup("");
			if (!value)
				error_handler(NULL, ENOMEM);
		}
	}
	(*i)--;
	return (value);
}

char	*handle_dollar_in_line(char *line, t_all *all)
{
	int		i;
	int		start;
	char	*new_line;
	char	*sub_str;


	if (!ft_strchr(line, '$') || is_last_token_escaped(all->lst_token) & ESCAPED_CHAR)
		return (line);
	i = -1;
	new_line =  ft_strdup("");
	if (!new_line)
		error_handler(NULL, ENOMEM);
	
	while(line[++i])
	{
		start = i;
		while (line[i] != '$' && line[i])
			i++;
		if (i- start > 0)
		{
			sub_str = ft_substr(line, start, i - start);
			new_line = ft_strjoin(new_line, sub_str);
			if (sub_str)
				free(sub_str);
			if (!new_line)
				error_handler(NULL, ENOMEM);
		}
		if (line[i] == '$')
		{
			new_line = ft_strjoin(new_line, get_variable_value(line, all, &i));
			if (!new_line)
				error_handler(NULL, ENOMEM);
		}
	}
	return (new_line);
}

void	open_fd_here_document(t_all *all, t_dlst **ptr_token)
{
	t_dlst	*tmp;
	char	*line;
	int		ret;

	tmp = *ptr_token;
	go_to_end_or_separator(&tmp);
	if (tmp->next)
	{
		while (1)
		{
			//ft_putstr_fd("> ", STDIN_FILENO);
			ret = read_line(all->fd_in, &line);
			if (ret < 0)
				error_handler(NULL, errno);
			if (!ft_strcmp(line, tmp->next->str))
			{
				free(line);
				break ;
			}
			line = handle_dollar_in_line(line, all);
			ft_putendl_fd(line, all->fd_out);
			free(line);
			line  = NULL;
		}
	}
}