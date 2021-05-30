/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:30:10 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/30 22:54:55 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	remove_variable(char *name, t_dlst *lst_env)
{
	int		len;

	while (lst_env)
	{
		len = ft_strlen(name);
		if (!ft_strncmp(name, lst_env->str, len) && lst_env->str[len] == '=')
		{
			doubly_lst_delete_element(&lst_env);
			return ;
		}
		lst_env = lst_env->next;
	}
}

int	unset_cmd(t_dlst **ptr_token, t_dlst *lst_env)
{
	int	status;

	*ptr_token = (*ptr_token)->next;
	if (!lst_env)
		return (errno = ERROR);
	status = 0;
	while (*ptr_token && !is_separator((*ptr_token)->str))
	{
		if (is_valid_variable_name((*ptr_token)->str, '\0'))
			remove_variable((*ptr_token)->str, lst_env);
		else
		{
			status = ERROR;
			errno = ERROR;
			cmd_error_message("unset", (*ptr_token)->str,
				"not a valid identifier");
		}
		*ptr_token = (*ptr_token)->next;
	}
	return (status);
}
