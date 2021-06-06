/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrdima <mrdima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:09:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 16:31:23 by mrdima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"
# include "error_handlers.h"
# include "environment.h"

# define RED_COLOR	"\033[1;31m"
# define NONE_COLOR "\033[0;0m"

int		builtins(t_dlst **ptr_token, t_all *all);
int		echo_cmd(t_dlst **ptr_token, int fd_out);
int		unset_cmd(t_dlst **ptr_token, t_dlst *env);
int		env_cmd(t_dlst **ptr_token, t_dlst *env, int fd_outs);
int		pwd_cmd(t_dlst **ptr_token, int fd_outs);
int		export_cmd(t_dlst **ptr_token, t_dlst *env, int fd_out);
int		cd_cmd(t_dlst **ptr_token, t_dlst *env);
int		is_valid_variable_name(char *variable_name, char end_char);
int		exit_cmd(t_dlst **ptr_token, unsigned char exit_status,
			t_dlst **shell_hist);
void 	save_history_to_file_and_close(t_dlst **head_history);

#endif
