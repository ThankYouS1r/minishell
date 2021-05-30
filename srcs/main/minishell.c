/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/30 22:55:37 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer(t_all *all)
{
	t_dlst		*ptr_token;

	ptr_token = all->lst_token;
	all->exit_status = execute_builtin(&ptr_token, all);
	// if (!execute_builtin(&ptr_token, all))
	// 	execute_program(&ptr_token, all);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv) // TMP DELETE ME!
		return(error_handler("Too many arguments", 1));
	//set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &all);

	// open_minishell_history_file();
	while (1)
	{
		termcap_start();
		all.lst_token = parsing(&all);
		if (all.lst_token)
			executer(&all);
		doubly_lst_clear(&all.lst_token);
	}
	//close_minishell_history_file();
	doubly_lst_clear(&all.lst_env);
	return (0);
}
