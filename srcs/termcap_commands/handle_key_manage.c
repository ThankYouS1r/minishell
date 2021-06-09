#include "termcap_commands.h"

char	*escape_press(t_all *all)
{
	int 	counter;

	counter = all->sh_counter;
	if (counter >= 1 && all->cursor_counter >= 12)
	{
		if (all->sh_counter >= 1)
			--all->sh_counter;
		tputs(tgetstr("le", NULL), 1, myputchar);
		tputs(tgetstr("dc", NULL), 1, myputchar);
		if (counter == 1)
		{
			free(all->line);
			all->line = NULL;
			return (all->line);
		}
		else if (counter > 1)
		{
			all->line = ft_realloc(all->line, counter);
			all->line[--counter] = '\0';
		}
		--all->cursor_counter;
	}
	return (all->line);
}

char	*printf_symbols(char c, t_all *all)
{
	int 	counter;

	counter = all->sh_counter;
	if (counter >= 0)
	{
		all->line = ft_realloc(all->line, counter + 2);
		all->line[counter] = c;
		all->line[++counter] = '\0';
		ft_putchar_fd(c, 1);
		++all->sh_counter;
		++all->cursor_counter;
	}
	return (all->line);
}

char	*enter_press(t_all * all)
{
	int 	counter;

	counter = all->sh_counter;
	if (counter == 0)
	{
		free(all->line);
		all->line = NULL;
	}
	write(1, "\n", 1);
	return (all->line);
}

char		*history_operation(t_dlst **ptr_history, t_all *all, int iter_hist)
{
	char 	*left_step;
	char 	*delete_char;

	left_step = tgetstr("cr", NULL);
	if (!left_step)
		ft_crash("temp_error");
	delete_char = tgetstr("dl", NULL);
	if (!delete_char)
		ft_crash("temp_error");
	tputs(left_step, 1, myputchar);
	tputs(delete_char, 1, myputchar);
	print_logo();
	print_minishell_history(ptr_history, iter_hist);
	all->line = ft_strdup((*ptr_history)->str);
	if (!all->line)
		ft_crash("temp_error");
	ft_putstr_fd(all->line, 1);
	all->sh_counter = ft_strlen(all->line);
	all->cursor_counter = 12 + all->sh_counter;;
	return (all->line);
}

void 	ctrld_press(t_all *all, t_dlst **ptr_history, int counter)
{
	char	*str;
	int 	i = 0;

	if (counter == 0 && !all->line)
	{
		write(1, "exit", 4);
		if (ptr_history) //Не забыть все очистить
			i = 1;
		(void)i;	//TMP! DELETE ME! (variable ‘i’ set but not used)
		ft_crash(" do svyazi");
	}
	else
	{
		str = tgetstr("bl", NULL);
		if (!str)
			ft_crash("temp_error");
		tputs(str, 1, myputchar);
	}
}

char  *ctrlc_press(t_all *all)
{
	if (all->line)
		free(all->line);
	all->line = ft_strdup(" ");
	all->cursor_counter = 12;
	all->sh_counter = 0;
	print_logo();
	return (all->line);
}

char  *ctrll_press(t_all *all)
{
	char 	*clear_scr;

	clear_scr = tgetstr("cl", NULL);
	if (!clear_scr)
		ft_crash("temp_error");
	tputs(clear_scr, 1, myputchar);
	print_logo();
	if (all->line && all->sh_counter > 0 && all->cursor_counter > 10)
	{
		ft_putstr_fd(all->line, 1);
		all->sh_counter = ft_strlen(all->line);
		all->cursor_counter = 12 + all->sh_counter;;
	}
	return (all->line);
}