#include "signal_handlers.h"

void	handle_sigint(int signum)
{
	(void)signum;
	write(1, "\n", 1) ;// TMP
}

void	handle_sigquit(int signum)
{
	(void)signum; // TMP
	ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
}


void	set_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
