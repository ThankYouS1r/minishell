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

int	open_fd_here_document(t_all *all, t_dlst **ptr_token)
{
	// int		fd;
	t_dlst	*tmp;
	char	*line;
	int		ret;

	tmp = *ptr_token;
	go_to_end_or_separator(&tmp);
	if (tmp->next)
	{
		// fd = open("tmpheredocument", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		// if (fd < 0)
		// {
		// 	(cmd_error_message(NULL, tmp->next->str, strerror(errno)));
		// 	while (*ptr_token)
		// 		*ptr_token = (*ptr_token)->next;
		// 	all->exit_status = 1;
		// 	return (STDOUT_FILENO);
		// }
		while (1)
		{
			ret = read_line(all->fd_in, &line);
			if (ret < 0)
				error_handler(NULL, errno);
			if (!ft_strcmp(line, tmp->next->str) || ret == 0)
				break ;
		}
		// if (all->fd_in != STDIN_FILENO)
		// 	close(all->fd_in);
		// fd = open(tmp->next->str, O_RDONLY, S_IRWXU);
		// if (fd < 0)
		// {
		// 	(cmd_error_message(NULL, tmp->next->str, strerror(errno)));
		// 	while (*ptr_token)
		// 		*ptr_token = (*ptr_token)->next;
		// 	all->exit_status = 1;
		// 	return (STDIN_FILENO);
		// }
		// return (fd);
	}
	return (all->fd_in);
}