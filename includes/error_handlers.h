/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:03:33 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/05 23:19:57 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLERS_H
# define ERROR_HANDLERS_H

# define RED_COLOR	"\033[1;31m"
# define NONE_COLOR "\033[0;0m"

# include <errno.h>
# include "libft.h"
# include "utils.h"

int		error_handler(const char *message, int error_code);
void	cmd_error_message(char *cmd_name, char *arg_name, char *description);
void	syntax_error_message(t_all *all, t_dlst **ptr_token);

#endif
