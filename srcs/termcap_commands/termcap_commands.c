#include "termcap_commands.h"

static int	myputchar(int nb)
{
	return (write (1, &nb, 1));
}

struct termios init_settings(void)
{
	int				check_get;
	struct termios	term;
	struct termios	saved_attributes;

	check_get = 0;
	tcgetattr(0, &saved_attributes); //Получить атрибут терминала. Данные будут записаны в структуру term
	memcpy(&term, &saved_attributes, sizeof(term));
	term.c_lflag &= ~(ECHO); //Без этого флага не будет отображения набираемых символов
	term.c_lflag &= ~(ICANON); //Не канонический режим. В каноническом read завершается по нажатию enter
	tcsetattr(0, TCSANOW, &term); //Установить атрибут терминала. Вернуть параметры в терминал
	check_get = tgetent(0, getenv("TERM")); //ЗАГРУЗИТЬ ДАННЫЕ ИЗ МАССИВА //Загружаем базу данных оригинального терминала. Первый параметр не нужен, так как более нигде не используется
	if (check_get == -1)
		ft_crash("Error");
	return (saved_attributes);
}

char  *save_str(char *str, char *struct_str, int i)
{
	if (i == 1)
	{
		struct_str = ft_malloc(2);
		struct_str[0] = str[0];
		struct_str[1] = '\0';
	}
	else if (i > 1)
	{
		struct_str = ft_realloc(struct_str, i);
		struct_str[i - 1] = str[0];
		struct_str[i] = '\0';
	}
	return (struct_str);
}

char	*escape_press(int counter, t_all *all)
{
	int 	j;

	j = counter;
	if (j >= 1 && all->cursor_counter >= 12)
	{
		tputs(tgetstr("le", NULL), 1, myputchar);
		tputs(tgetstr("dc", NULL), 1, myputchar);
		if (j == 1)
		{
			free(all->line);
			all->line = ft_strdup("");
			return (all->line);
		}
		else if (j > 1)
		{
			all->line = ft_realloc(all->line, j);
			all->line[--j] = '\0';
		}
		--all->cursor_counter;
	}
	return (all->line);
}

char	*printf_symbols(char c, t_all *all, int *counter)
{
	int 	j;

	j = *counter;
	if (j == 0)
	{
		all->line = ft_malloc(2); //Говнокод
		all->line[0] = c;
		all->line[1] = '\0';
	}
	else if (j > 0)
	{
		all->line = ft_realloc(all->line, j + 2);
		all->line[j] = c;
		all->line[++j] = '\0';
	}
	ft_putchar_fd(c, 1);
	++*counter;
	++all->cursor_counter;
	return (all->line);
}

char	*enter_press(t_all * all, int counter)
{
	if (counter == 0)
	{
		free(all->line);
		all->line = ft_strdup("");
	}
	return (all->line);
}

void 	printf_logo(void)
{
	write (1, "\033[0;32mminishell-> ", 19);
	write (1, "\033[0;0m", 6);
}

void 	ft_parse_args(struct termios s_ats, t_all *all, t_dlst **ptr_history)
{
	char		str[1000];
	int			ret;
	int 		counter;

	// Защитить ft_strdup

	counter = 0;
	while ((ret = read(0, str, 100))) //идти до CTRL + D(004 по терминалу)
	{
		str[ret] = 0;
		if (!ft_strncmp(str, K_CTRL_D, 3))
			break;
		else if (!strcmp(str, tgetstr("kb", NULL)) || !strcmp(str, "\177"))
		{
			all->line = escape_press(counter, all);
			if (counter >= 1)
				--counter;
		}
		else if (!ft_strncmp(str, K_UP, 3) && strcmp(str, "\n"))
		{
			// Отдельно вызвать tgetstr,  сделать пару проверок на вызов этих функций
			tputs(tgetstr("cr", NULL), 1, myputchar);
			tputs(tgetstr("dl", NULL), 1, myputchar);
			//
			printf_logo();
			print_minishell_history(ptr_history, PREVIOUS_HISTORY);
			all->line = ft_strdup((*ptr_history)->str);
			if (!all->line)
				ft_crash("temp_error");
			ft_putstr_fd(all->line, 1);
			counter = ft_strlen(all->line);
			all->cursor_counter = 12 + counter;
		}
		else if (!ft_strncmp(str, K_DOWN, 3))
		{
			tputs(tgetstr("cr", NULL), 1, myputchar);
			tputs(tgetstr("dl", NULL), 1, myputchar);
			printf_logo();
			print_minishell_history(ptr_history, NEXT_HISTORY);
			all->line = ft_strdup((*ptr_history)->str);
			if (!all->line)
				ft_crash("temp_error");
			ft_putstr_fd(all->line, 1);
			counter = ft_strlen(all->line);
			all->cursor_counter = 12 + counter;
		}
		else if (!strcmp(str, tgetstr("kD", NULL)))
			tputs(tgetstr("dc", NULL), 1, myputchar);
		else if (*str == 10)
		{
			all->line = enter_press(all, counter);
			break;
		}
		else if (str[0] > 31 && str[0] < 127)
			all->line = printf_symbols(str[0], all, &counter);
	}
	write (1, "\n", 1);
	tcsetattr(0, TCSANOW, &s_ats);
}

void 	termcap_start(t_all *all, t_dlst **ptr_history)
{
	struct termios saved_attributes;

	printf_logo();
	all->cursor_counter = 11;
	saved_attributes = init_settings();
	ft_parse_args(saved_attributes, all, ptr_history);
}


//		else if (!ft_strncmp(str, K_LEFT, 3) && all->cursor_counter >= 12) В ОСНОВНОЙ ЧАСТИ ИХ ОБРАБАТЫВАТЬ(РЕДАКТИРОВАТЬ СТРОКУ) НЕ ТРЕБУЮТ. ПОКА ОСТАВЛЮ НА ПЕРСПЕКТИВУ
//		{
//			j++;
//			tputs(tgetstr("le", NULL), 1, myputchar);
//			--counter;
//			--all->cursor_counter;
//		}
//		else if (!ft_strncmp(str, K_RIGHT, 3) && j > 0)
//		{
//			tputs(tgetstr("nd", NULL), 1, myputchar);
//			j--;
//			++counter;
//			++all->cursor_counter;
//		}
