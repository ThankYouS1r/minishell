/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:32:20 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/03 21:06:18 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include "signal_handlers.h"
# include "environment.h"
# include "parsing.h"
# include "termcap_commands.h"
# include "builtins.h"
# include "exec_commands.h"

void	open_history_file(t_dlst **head_history, t_dlst **ptr_history);


#endif
