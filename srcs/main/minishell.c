#include "minishell.h"

void	exec_builtins_or_external_programs(t_all *all, t_dlst **ptr_token)
{
	if (!builtins(ptr_token, all) && !external_programs(ptr_token, all))
	{
		cmd_error_message((*ptr_token)->str, NULL, "command not found");
		go_to_end_or_separator(ptr_token);
		all->exit_status = 127;
	}
}

int	executer(t_all *all)
{
	t_dlst		*ptr_token;
	int			fd[2];

	ptr_token = all->lst_token;
	if (is_separator(ptr_token))
		syntax_error_message(all, &ptr_token);
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
		exec_builtins_or_external_programs(all, &ptr_token);
		close_fds(all);
		if (all->next_operator == PIPE)
			all->fd_in = fd[0];
		else
			all->fd_in = STDIN_FILENO;
		if (ptr_token && (is_separator(ptr_token)))
			ptr_token = ptr_token->next;
	}
	close_fds(all);
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
