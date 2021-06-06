/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:35:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 08:20:45 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_cmd(t_dlst **ptr_token, int fd_out)
{
	int	n_option;

	n_option = 0;
	*ptr_token = (*ptr_token)->next;
	if (*ptr_token && !ft_strcmp((*ptr_token)->str, "-n"))
	{
		n_option = 1;
		*ptr_token = (*ptr_token)->next;
	}
	while (*ptr_token && !is_separator(*ptr_token))
	{
		ft_putstr_fd((*ptr_token)->str, fd_out);
		if ((*ptr_token)->next && !is_separator((*ptr_token)->next))
			write(fd_out, " ", 1);
		*ptr_token = (*ptr_token)->next;
	}
	if (!n_option)
		write(fd_out, "\n", 1);
	return (SUCCESS);
}
