/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/04 19:20:06 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_operator(t_dlst *ptr_token)
{
	while (ptr_token->next && !is_separator(ptr_token->str))
		ptr_token = ptr_token->next;
	return (is_separator(ptr_token->str));
}

void	executer(t_all *all)
{
	t_dlst		*ptr_token;
	int			fd[2];

	ptr_token = all->lst_token;
	if (is_separator(ptr_token->str))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(ptr_token->str, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		ptr_token = ptr_token->next;
		go_to_end_or_separator(&ptr_token);
		all->exit_status = 2;
	}
	while (ptr_token)
	{
		all->next_operator = next_operator(ptr_token);
		if (all->next_operator == PIPE)
		{
			if (pipe(fd) < 0)
				(error_handler(NULL, errno));//return (error_handler(NULL, errno));
		}
		if (!execute_builtin(&ptr_token, all) &&
			!execute_program(&ptr_token, all))
		{
			cmd_error_message(ptr_token->str, NULL, "command not found");
			go_to_end_or_separator(&ptr_token);
			all->exit_status = 127;
		}
		if (ptr_token && !ft_strcmp(ptr_token->str, ";"))
			ptr_token = ptr_token->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv)
		return(error_handler("Wrong arguments", 1));
	set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &all);
	open_history_file(&all.shell_history, &all.ptr_history);
	while (1)
	{
		termcap_start(&all.ptr_history);
		all.lst_token = parsing(&all);
		if (all.lst_token)
			executer(&all);
		doubly_lst_clear(&all.lst_token);
	}
	save_history_to_file_and_close(&all.shell_history);
	doubly_lst_clear(&all.env);
	return (0);
}
