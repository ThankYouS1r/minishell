/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:26:28 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/20 12:11:30 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "error_handlers.h"
# include "utils.h"
# include "minishell.h"

char			*read_line(void);
int				is_double_quotes(char ch);
int				is_single_quotes(char ch);
int				is_slash(char ch);
int				is_dollar(char ch);
int				is_spec_symbols(char ch);
t_doubly_lst	*parsing();

#endif