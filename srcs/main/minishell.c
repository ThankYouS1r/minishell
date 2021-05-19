/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 12:26:11 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	struct termios saved_attributes;

	if (argc != 1 || !argv) // TMP DELETE ME!
		ft_crash("Arg error");
	set_environment((const char **)envp, &env);
	//write(2, "\033[1;33m", 7);
	write (1, "\033[0;32mminishell->", 18);
	saved_attributes = ft_init_settings();
	ft_parse_args(argc, argv, saved_attributes);
//	set_signal_handlers(); // Will be done a litle bit later
	return (0); // Temp! Replace me!!!
}
