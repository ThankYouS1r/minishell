#include "minishell.h"

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

int	open_fd_in_redirect(t_all *all, t_dlst **ptr_token)
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

t_dlst	*check_syntax_and_get_token_pos(t_all *all)
{
	t_dlst	*ptr_token;
	t_dlst	*tmp;

	ptr_token = all->lst_token;
	tmp = ptr_token;
	while (tmp->next)
		tmp = tmp->next;
	if (is_separator(ptr_token) == PIPE || is_separator(ptr_token) == SEMICOLON)
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
	if (*ptr_token && (is_separator(*ptr_token) == REDIRECT_INPUT))
	{
		*ptr_token = (*ptr_token)->next;
		go_to_end_or_separator(ptr_token);
	}
	if (*ptr_token && (is_separator(*ptr_token)))
		*ptr_token = (*ptr_token)->next;
}

int	executer(t_all *all)
{
	t_dlst		*ptr_token;
	int			fd[2];

	ptr_token = check_syntax_and_get_token_pos(all);
	while (ptr_token)
	{
		all->next_operator = next_operator(ptr_token);
		if (all->next_operator == PIPE)
		{
			if (pipe(fd) < 0)
				return (error_handler(NULL, errno));
			all->fd_out = fd[1];
		}
		else
			all->fd_out = STDOUT_FILENO;
		if (all->next_operator == REDIRECT_INPUT)
			all->fd_in = open_fd_in_redirect(all, &ptr_token);
		exec_builtins_or_external_programs(all, &ptr_token);
		close_fds(all);
		if (all->next_operator == PIPE)
			all->fd_in = fd[0];
		else
			all->fd_in = STDIN_FILENO;
		skip_separator(&ptr_token);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv)
		return (error_handler("Wrong arguments", 1));
	set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &all);
	open_history_file(&all.shell_history, &all.ptr_history);
	while (1)
	{
		//termcap_start(&all.ptr_history);
		all.lst_token = parsing(&all);
		if (all.lst_token)
			executer(&all);
		doubly_lst_clear(&all.lst_token);
	}
	save_history_to_file_and_close(&all.shell_history);
	doubly_lst_clear(&all.env);
	return (0);
}
