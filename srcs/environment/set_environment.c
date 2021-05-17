/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:25:30 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/17 10:45:24 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env *set_environment(const char *envp[], t_env *env)
{
	env->nbr_variables = -1;
	while (*envp)
		ft_strchr(*envp[++env->nbr_variables], '=');
	if (!env->nbr_variables)
		return (0);
	return (env);
}
