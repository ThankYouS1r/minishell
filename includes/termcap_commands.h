/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:32:54 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/05 17:35:41 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TERMCAP_COMMANDS_H
# define TERMCAP_COMMANDS_H

# include <termios.h>
# include <term.h>
# include <curses.h>
# include "utils.h"
# include "libft.h"
# include "parsing.h"

# define K_UP	"\e[A"
# define K_DOWN 	"\e[B"
# define K_LEFT 	"\e[D"
# define K_RIGHT "\e[C"
# define K_CTRL_D "\4"
# define K_ENTER	"\10"


typedef struct	s_termcap
{
	char		*str;
	int			count;
}				t_termcap;

void		termcap_start(t_all *all, t_dlst **ptr_history);
void		print_minishell_history(t_dlst **ptr_history, int direction);
void 		ft_parse_args(struct termios s_ats, t_all *all, t_dlst **ptr_history);


#endif
