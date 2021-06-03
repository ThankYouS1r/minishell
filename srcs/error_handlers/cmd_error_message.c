/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error_message.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:24:47 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/03 22:37:03 by eluceon          ###   ########.fr       */
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
