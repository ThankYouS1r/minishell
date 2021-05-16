/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:25:30 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/16 19:54:21 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

t_env *set_environment(const char *envp[])
{
	t_env	env;

	size_t	nbr_variables;

	env.nbr_variables = -1;
	while (*envp)
		ft_strchr(*envp[++env.nbr_variables], '=');
	if (!env.nbr_variables)
		retrun (0);
	return (&env);
}
