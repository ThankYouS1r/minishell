/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:25:30 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/17 16:24:12 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env *set_environment(const char *envp[], t_env *env)
{
	env->size = 0;
	while (envp[env->size])
		ft_strchr(envp[env->size++], '=');
	if (!env->size)
		return (NULL);
	env->array  = duplicate_string_array(envp, env->size);
	if (!env->array)
		return (NULL);
	return (env);
}
