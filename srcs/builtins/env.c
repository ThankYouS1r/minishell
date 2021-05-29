/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:17:23 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/29 21:12:48 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		env_cmd(t_dlst **ptr_token, t_dlst *lst_env)
{
	*ptr_token = (*ptr_token)->next;
	if (!lst_env)
		return (errno = 126);
	while (*ptr_token && !is_separator((*ptr_token)->str))
		*ptr_token = (*ptr_token)->next;
	while (lst_env)
	{
		ft_putendl_fd(lst_env->str, STDOUT_FILENO);
		lst_env = lst_env->next;
	}
	return (SUCCESS);
}
