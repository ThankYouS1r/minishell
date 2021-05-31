/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:09:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/31 15:01:43 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "error_handlers.h"
# include "environment.h"

# define RED_COLOR	"\033[1;31m"
# define NONE_COLOR "\033[0;0m"

int		execute_builtin(t_dlst **ptr_token, t_all *all);
int		echo_cmd(t_dlst **ptr_token);
int		unset_cmd(t_dlst **ptr_token, t_dlst *env);
void	cmd_error_message(char *cmd_name, char *arg_name, char *description);
int		env_cmd(t_dlst **ptr_token, t_dlst *env);
int		pwd_cmd(t_dlst **ptr_token);
int		export_cmd(t_dlst **ptr_token, t_dlst *env);
int		cd_cmd(t_dlst **ptr_token, t_dlst *env);
int		is_valid_variable_name(char *variable_name, char end_char);

#endif
