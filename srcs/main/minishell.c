/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/03 21:28:09 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_all *all)
{
	t_dlst		*ptr_token;

	ptr_token = all->lst_token;
	if (!execute_builtin(&ptr_token, all) && !execute_program(&ptr_token, all))
	{
		cmd_error_message(ptr_token->str, NULL, "command not found");
		all->exit_status = 127;
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
