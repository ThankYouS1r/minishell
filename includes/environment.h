/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:29:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/18 12:21:47 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include "utils.h"

typedef struct s_env
{
	// More data will be added later!
	size_t		size;
	char		**array;
}				t_env;

t_env *set_environment(const char *envp[], t_env *env);
char	*getenv_from_array(const char *array[], const char *name);

#endif
