/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 08:58:31 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 14:44:16 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_env	env;

	if (!argc || !argv) // TMP DELETE ME!
		return (1);
//	set_signal_handlers(); // Will be done a litle bit later
	set_environment((const char **)envp, &env);
	termcap_start();
	return (0); // Temp! Replace me!!!
}
