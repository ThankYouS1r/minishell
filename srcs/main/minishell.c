/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/20 12:53:09 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env			env;
	t_doubly_lst	*token_lst;

	token_lst = NULL;
	if (argc != 1 || !argv) // TMP DELETE ME!
		ft_crash("Too many arguments");
//	set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &env);
	termcap_start();
	token_lst = parsing(token_lst);
	while (token_lst)
	{
		printf("%s\n", token_lst->str);
		token_lst = token_lst->next;
	}
	//executer(tokens);
	return (0); // Temp! Replace me!!!
}
