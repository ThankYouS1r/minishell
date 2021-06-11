#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H

# include <signal.h>
# include "libft.h"
# include "utils.h"

extern int g_sigint;

void	set_signal_handlers(void);

#endif
