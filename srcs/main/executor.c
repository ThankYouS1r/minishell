#include <minishell.h>

void	exec_builtins_or_external_programs(t_all *all, t_dlst **ptr_token)
{
	if (!*ptr_token)
		return ;
	else if (!builtins(ptr_token, all) && !external_programs(ptr_token, all))
	{
		cmd_error_message((*ptr_token)->str, NULL, "command not found");
		go_to_end_or_separator(ptr_token);
		all->exit_status = 127;
	}
}

t_dlst	*check_syntax_and_get_token_pos(t_all *all)
{
	t_dlst	*ptr_token;
	t_dlst	*tmp;

	ptr_token = all->lst_token;
	tmp = ptr_token;
	while (tmp->next)
		tmp = tmp->next;
	if (ptr_token->flag == ESCAPED_CHAR)
		return (ptr_token);
	else if (is_separator(ptr_token) == PIPE || is_separator(ptr_token) == SEMICOLON)
		syntax_error_message(all, &ptr_token, ptr_token->str);
	else if ((is_separator(tmp) == PIPE)
		|| (is_separator(tmp) == SEMICOLON
			&& is_separator(tmp->prev) == SEMICOLON)
		|| (is_separator(tmp) == SEMICOLON && is_separator(tmp->prev)))
		syntax_error_message(all, &ptr_token, tmp->str);
	else if (is_separator(tmp) && is_separator(tmp) != SEMICOLON)
		syntax_error_message(all, &ptr_token, "newline");
	return (ptr_token);
}

void	skip_separator(t_dlst **ptr_token)
{
	if (*ptr_token && (is_separator(*ptr_token) == REDIRECT_INPUT
        || is_separator(*ptr_token) == REDIRECT_OUTPUT
		|| is_separator(*ptr_token) == APPEND_REDIRECT_OUTPUT
		|| is_separator(*ptr_token) == HERE_DOCUMENT))
	{
		*ptr_token = (*ptr_token)->next;
		go_to_end_or_separator(ptr_token);
	}
	if (*ptr_token && (is_separator(*ptr_token)))
		*ptr_token = (*ptr_token)->next;
}

int	executor_loop(t_all *all)
{
	t_dlst		*ptr_token;
	int			fd[2];

	ptr_token = check_syntax_and_get_token_pos(all);
	while (ptr_token)
	{
		all->next_operator = next_operator(ptr_token);
		if (all->next_operator == PIPE || all->next_operator == HERE_DOCUMENT)
		{
			if (pipe(fd) < 0)
				return (error_handler(NULL, errno));
			all->fd_out = fd[1];
		}
		else
			all->fd_out = STDOUT_FILENO;
		if (all->next_operator == REDIRECT_INPUT)
			all->fd_in = open_fd_input_redirect(all, &ptr_token);
        else if (all->next_operator == REDIRECT_OUTPUT
            || all->next_operator == APPEND_REDIRECT_OUTPUT)
			all->fd_out = open_fd_output_redirect(all, &ptr_token);
		else if (all->next_operator == HERE_DOCUMENT)
		{
			open_fd_here_document(all, &ptr_token);
			close(all->fd_out);
			all->fd_in = fd[0];
		}
		exec_builtins_or_external_programs(all, &ptr_token);
		close_fds(all);
		if (all->next_operator == PIPE)
			all->fd_in = fd[0];
		else
			all->fd_in = STDIN_FILENO;
		skip_separator(&ptr_token);
	}
	return (all->exit_status);
}
