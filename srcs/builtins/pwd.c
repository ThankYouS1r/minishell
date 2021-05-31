/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 21:29:36 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/31 14:17:14 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		pwd_cmd(t_dlst **ptr_token)
{
	char	*cwd;

	*ptr_token = (*ptr_token)->next;
	go_to_end_or_separator(ptr_token);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd_error_message("pwd", NULL, strerror(errno));
		return (errno);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (SUCCESS);
}
