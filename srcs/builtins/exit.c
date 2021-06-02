/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 21:35:26 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/01 21:36:27 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int exit_cmd(t_dlst **ptr_token, unsigned char exit_status)
{
    unsigned char status;

    status = 0;
    *ptr_token = (*ptr_token)->next;
    ft_putendl_fd("exit", STDERR_FILENO);
	if (!(*ptr_token))
        status = exit_status;
    else if (!is_number((*ptr_token)->str) && !is_separator((*ptr_token)->str))
	{
		cmd_error_message("exit", (*ptr_token)->str,
			"numeric argument required");
		go_to_end_or_separator(ptr_token);
		status = 2;
	}
    else if (!is_separator((*ptr_token)->str)
		&& (*ptr_token)->next && !is_separator((*ptr_token)->next->str))
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
    exit(status);
}
