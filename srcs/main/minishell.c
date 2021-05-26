/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/25 15:33:13 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv) // TMP DELETE ME!
		return(error_handler("Too many arguments", 1));
//	set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &all.env);
	// open_minishell_history_file();
	while(1)
	{
	//	termcap_start();
		all.lst_token = parsing(&all);
		while (all.lst_token) // TESTING LIST. DELETE ME LATER!!!!
		{
			printf("%s\n", all.lst_token->str);
			all.lst_token = all.lst_token->next;
		}
		//executer(&all);
	}
	//close_minishell_history_file();
	return (0); // Temp! Replace me!!!
}
