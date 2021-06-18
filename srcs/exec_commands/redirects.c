#include "exec_commands.h"


int	open_fd_output_redirect(t_all *all, t_dlst **ptr_token, t_dlst *tmp_token)
{
	int		fd;

	go_to_end_or_separator(&tmp_token);
	if (tmp_token->next)
	{
		if (all->fd_in != STDIN_FILENO)
			close(all->fd_in);
		fd = open(tmp_token->next->str, O_RDONLY, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp_token->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDIN_FILENO);
		}
		return (fd);
	}
	return (all->fd_in);
}

int     open_fd_input_redirect(t_all *all, t_dlst **ptr_token, t_dlst*tmp_token)
{
    int		fd;

	fd = STDOUT_FILENO;
    if (tmp_token)
	{
		if (all->fd_out != STDOUT_FILENO)
			close(all->fd_out);
        if (all->next_operator == REDIRECT_OUTPUT)
		    fd = open(tmp_token->next->str, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
        else if (all->next_operator == APPEND_REDIRECT_OUTPUT)
		    fd = open(tmp_token->next->str, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		if (fd < 0)
		{
			(cmd_error_message(NULL, tmp_token->next->str, strerror(errno)));
			while (*ptr_token)
				*ptr_token = (*ptr_token)->next;
			all->exit_status = 1;
			return (STDOUT_FILENO);
		}
		return (fd);
	}
	return (all->fd_out);
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
		(*i)++;
		return (value);
	}
	while (line[*i] && (line[*i]== '_' || ft_isalpha(line[*i]))
		&& !ft_iswhitespace(line[*i]))
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
	return (value);
}

char	*handle_dollar_in_line(char *line, t_all *all)
{
	int		i;
	int		start;
	char	*new_line;
	char	*sub_str;
	char	*tmp;


	if (!ft_strchr(line, '$') || is_last_token_escaped(all->lst_token) & ESCAPED_CHAR)
		return (line);
	i = 0;
	new_line =  ft_strdup("");
	if (!new_line)
		error_handler(NULL, ENOMEM);
	
	while(line[i])
	{
		start = i;
		while (line[i] != '$' && line[i])
			i++;
		if (i- start > 0)
		{
			sub_str = ft_substr(line, start, i - start);
			tmp = new_line;
			new_line = ft_strjoin(tmp, sub_str);
			free(tmp);
			if (sub_str)
				free(sub_str);
			if (!new_line)
				error_handler(NULL, ENOMEM);
		}
		if (line[i] == '$')
		{
			tmp = new_line;
			sub_str = get_variable_value(line, all, &i);
			if (!sub_str)
				error_handler(NULL, ENOMEM);
			new_line = ft_strjoin(tmp, sub_str);
			free(tmp);
			free(sub_str);
			if (!new_line)
				error_handler(NULL, ENOMEM);
		}
	}
	free(line);
	return (new_line);
}

void	open_fd_here_document(t_all *all, t_dlst **ptr_token)
{
	t_dlst	*tmp;
	char	*line;
	int		ret;

	tmp = *ptr_token;
	go_to_end_or_separator(&tmp);
	while (tmp->next)
	{
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

void	redirections(t_all *all, t_dlst **ptr_token)
{
	t_dlst	*tmp_token;
	int		fd[2];

    tmp_token = *ptr_token;
	while (all->next_operator == REDIRECT_INPUT
		|| all->next_operator == REDIRECT_OUTPUT
		|| all->next_operator == APPEND_REDIRECT_OUTPUT
		|| all->next_operator == HERE_DOCUMENT)
	{
   		go_to_end_or_separator(&tmp_token);
		if (all->next_operator == REDIRECT_INPUT)
			all->fd_in = open_fd_output_redirect(all, ptr_token, tmp_token);
 	   	else if (all->next_operator == REDIRECT_OUTPUT
  	      || all->next_operator == APPEND_REDIRECT_OUTPUT)
			all->fd_out = open_fd_input_redirect(all, ptr_token, tmp_token);
		else if (all->next_operator == HERE_DOCUMENT)
		{
			if (pipe(fd) < 0)
				error_handler(NULL, errno);
			if (all->fd_out == STDOUT_FILENO)
				all->fd_out = fd[1];
			else
				close(fd[1]);
			close_fd(&all->fd_in, STDIN_FILENO);
			open_fd_here_document(all, &tmp_token);
			close_fds(all);
			all->fd_in = fd[0];
		}
		
		tmp_token = tmp_token->next;
		all->next_operator = next_operator(tmp_token);
	}
}