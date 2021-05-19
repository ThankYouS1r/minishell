/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:32:54 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 18:42:10 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef TERMCAP_COMMANDS_H
# define TERMCAP_COMMANDS_H

# include <termios.h>
# include <term.h>
# include <curses.h>
# include "utils.h"
# include "libft.h"

# define K_UP	"\e[A"
# define K_DOWN 	"\e[B"
# define K_CTRL_D "\4"
# define K_ENTER	"\10"

typedef struct	s_termcap
{
	char		*str;
	int			count;
}				t_termcap;

int	termcap_start(void);

#endif
