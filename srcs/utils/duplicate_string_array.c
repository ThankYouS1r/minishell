/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_string_array.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:16:00 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 09:43:30 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** The duplicate_string_array() function returns a pointer to a new string
** array which is a duplicate of the string array *str_array[].
** On success, the duplicate_string_array() function returns a pointer to the
** duplicated string array. It returns NULL if insufficient memory was
** available.
*/

char	**duplicate_string_array(const char *str_array[], size_t size)
{
	char	**new_str_array;
	int		i;

	new_str_array = (char **)ft_calloc(size + 1, sizeof(char *));
	if (!new_str_array)
		return (NULL);
	i = -1;
	while (++i < (int)size)
	{
		new_str_array[i] = ft_strdup(str_array[i]);
		if (!new_str_array[i])
		{
			while (--i >= 0)
			{
				free(new_str_array[i]);
				new_str_array[i] = NULL;
			}
			free(new_str_array);
			new_str_array = NULL;
			return (NULL);
		}
	}
	return (new_str_array);
}
