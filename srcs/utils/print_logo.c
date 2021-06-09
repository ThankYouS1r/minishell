#include "utils.h"

void 	print_logo(void)
{
	write (1, "\033[0;32mminishell-> ", 19);
	write (1, "\033[0;0m", 6);
}