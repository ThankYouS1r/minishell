/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:29:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/28 20:10:27 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "utils.h"
# include "error_handlers.h"


void	set_environment(const char *envp[], t_env *env);
char	*getenv_from_array(const char *array[], const char *name);

#endif
