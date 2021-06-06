/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrdima <mrdima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:24:47 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 17:12:07 by mrdima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	cmd_error_message(char *cmd_name, char *arg_name, char *description)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd(cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg_name)
	{
		ft_putstr_fd("`", STDERR_FILENO);
		ft_putstr_fd(arg_name, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putendl_fd(description, STDERR_FILENO);
}

void	syntax_error_message(t_all *all, t_dlst **ptr_token)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd((*ptr_token)->str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	*ptr_token = (*ptr_token)->next;
	go_to_end_or_separator(ptr_token);
	all->exit_status = 2;
}
