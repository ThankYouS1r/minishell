/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:57:15 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/04 14:38:36 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_COMMANDS_H
# define EXEC_COMMANDS_H

# include "environment.h"
# include "utils.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

int		execute_program(t_dlst **ptr_token, t_all *all);
char	**make_array_from_lst(t_dlst *head);
char	**make_arg_array_from_lst(t_dlst *head);
void	clear_array(char **str);

#endif
