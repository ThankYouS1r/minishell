/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:35:26 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 08:22:26 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exit_cmd(t_dlst **ptr_token, unsigned char exit_status, t_dlst **shell_hist)
{
	unsigned char	status;

	status = 0;
	*ptr_token = (*ptr_token)->next;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!(*ptr_token))
		status = exit_status;
	else if (!is_number((*ptr_token)->str) && !is_separator(*ptr_token))
	{
		cmd_error_message("exit", (*ptr_token)->str,
			"numeric argument required");
		go_to_end_or_separator(ptr_token);
		status = 2;
	}
	else if (!is_separator(*ptr_token)
		&& (*ptr_token)->next && !is_separator((*ptr_token)->next))
	{
		cmd_error_message("exit", NULL, "too many arguments");
		go_to_end_or_separator(ptr_token);
		status = 1;
	}
	else if (is_number((*ptr_token)->str))
	{
		status = ft_atoi((*ptr_token)->str);
		go_to_end_or_separator(ptr_token);
	}
	save_history_to_file_and_close(shell_hist);
	exit(status);
}
