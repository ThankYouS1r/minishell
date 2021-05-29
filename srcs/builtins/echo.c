/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:35:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/29 14:19:22 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	echo_cmd(t_dlst **ptr_token)
{
	int	n_option;

	n_option = 0;
	*ptr_token = (*ptr_token)->next;
	if (*ptr_token && !ft_strncmp((*ptr_token)->str, "-n", 3))
	{
		n_option = 1;
		*ptr_token = (*ptr_token)->next;
	}
	while (*ptr_token && !is_separator((*ptr_token)->str))
	{
		ft_putstr_fd((*ptr_token)->str, STDOUT_FILENO);
		if ((*ptr_token)->next && !is_separator((*ptr_token)->next->str))
			write(STDOUT_FILENO, " ", 1);
		*ptr_token = (*ptr_token)->next;
	}
	if (!n_option)
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
