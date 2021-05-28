/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:09:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/28 21:43:00 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "utils.h"

int		execute_builtin(t_dlst **ptr_token, t_all *all);
int		echo_cmd(t_dlst **ptr_token);

#endif
