/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:32:54 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 14:52:34 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TERMCAP_COMMANDS_H
# define TERMCAP_COMMANDS_H

# include <termios.h>
# include <term.h>
# include <curses.h>
# include "utils.h"
# include "libft.h"

typedef struct	s_parser
{
	char		*str;
	int			count;
}				t_parser;

int	termcap_start(void);

#endif
