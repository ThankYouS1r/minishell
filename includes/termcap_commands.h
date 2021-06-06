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

int		termcap_start(t_dlst **ptr_history);
void	print_minishell_history(t_dlst **ptr_history, int direction);


#endif
