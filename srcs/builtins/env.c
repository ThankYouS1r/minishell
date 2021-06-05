/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:17:23 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/03 20:08:49 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	env_cmd(t_dlst **ptr_token, t_dlst *env)
{
	*ptr_token = (*ptr_token)->next;
	go_to_end_or_separator(ptr_token);
	if (!env)
		return (errno = 126);
	while (env)
	{
		ft_putendl_fd(env->str, STDOUT_FILENO);
		env = env->next;
	}
	return (SUCCESS);
}
