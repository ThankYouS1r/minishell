/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/28 10:08:11 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_all	all;
	t_dlst 	*tmp; // TMP for printing! Delete me later!!!!!!1

	ft_bzero(&all, sizeof(t_all));
	if (argc != 1 || !argv) // TMP DELETE ME!
		return(error_handler("Too many arguments", 1));
	//set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &all.env);
	// open_minishell_history_file();
	while (1)
	{
		termcap_start();
		all.lst_token = parsing(&all);
		tmp = all.lst_token;
		while (tmp) // TESTING LIST. DELETE ME LATER!!!!
		{
			printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
		//executer(&all);
		doubly_lst_clear(&all.lst_token);
	}
	//close_minishell_history_file();
	free_doble_array(all.env.array);
	return (0); // Temp! Replace me!!!
}
