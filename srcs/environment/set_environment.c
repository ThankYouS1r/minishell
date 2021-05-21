/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_environment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:25:30 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/21 23:55:23 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** The getenv_from_array() function searches the environment array to find the
** environment variable name, and returns a pointer to the corresponding value
** string. Returns NULL if there is no match or malloc problem.
*/

char	*getenv_from_array(const char *array[], const char *name)
{
	size_t	i;
	size_t	j;
	char	*variable_value;

	if (!name || !array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j] && array[i][j] != '=' && array[i][j] == name[j])
		{
			if (array[i][j + 1] && array[i][j + 1] == '=')
			{
				variable_value = ft_strdup(array[i] + j + 2);
				if (!variable_value)
					return (NULL);
				return (variable_value);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
** The set_environment() parses environment variables and values, the result is
** stored in an array of strings.
*/

t_env	*set_environment(const char	*envp[], t_env *env)
{
	env->size = 0;
	while (envp[env->size])
		ft_strchr(envp[env->size++], '=');
	if (!env->size)
		return (NULL);
	env->array = duplicate_string_array(envp, env->size);
	if (!env->array)
		return (NULL);
	return (env);
}
