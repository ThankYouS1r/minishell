#include "termcap_commands.h"

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

void 	input_control(struct termios s_ats, t_all *all, t_dlst **ptr_history)
{
	char		str[1000];
	int			ret;

	// Защитить ft_strdup
	// Обработать сигнал control + косая черта (sigquit sigignore) + обработать сигнал ctrl + c
	// Если сохранить в историю команду на большое количество строк, то при перелистывании истории клавишами, на моменте вывода этой истории он будет сам принтить в терминал. Обработка множества строк - бонус
	// Доделать вывод начала истории
	//Не забыть все очистить в ctrld

	while ((ret = read(0, str, 100))) //идти до CTRL + D(004 по терминалу)
	{
		str[ret] = 0;
		
		if (!ft_strncmp(str, K_CTRL_D, 3) || *str == '\t')
			ctrld_press(all, ptr_history, all->sh_counter);
		else if (!ft_strcmp(str, "\177")) 	//!strcmp(str, tgetstr("kb", NULL)) временно убрал
			all->line = escape_press(all);
		else if (!ft_strncmp(str, K_UP, 3) && ft_strcmp(str, "\n") && *ptr_history)
			all->line = history_operation(ptr_history, all, PREVIOUS_HISTORY);
		else if (!ft_strncmp(str, K_DOWN, 3) && ft_strcmp(str, "\n") && *ptr_history)
			all->line = history_operation(ptr_history, all, NEXT_HISTORY);
		else if (*str == 12)
			all->line = ctrll_press(all);
		else if (*str == 3)
			all->line = ctrlc_press(all);
		else if (*str == 10 || !ft_strcmp(str, "\n"))
		{
			all->line = enter_press(all);
			break; 							//переделаю
		}
		else if (str[0] > 31 && str[0] < 127)
			all->line = printf_symbols(str[0], all);
		if (g_sigint) // Не работает корректно. Надо обработаь сигнал
		{
			free(all->line);
			all->line = NULL;
			all->sh_counter = 0; 
			all->cursor_counter = 12;
			all->exit_status = 130;
			g_sigint = 0;
		}
	}
	tcsetattr(0, TCSANOW, &s_ats);
}



void 	termcap_start(t_all *all, t_dlst **ptr_history)
{
	struct termios saved_attributes;

	print_logo();
	all->sh_counter = 0;
	all->cursor_counter = 12;
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	saved_attributes = init_settings();
	input_control(saved_attributes, all, ptr_history);
}


//		else if (!ft_strncmp(str, K_LEFT, 3) && all->cursor_counter >= 12)
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

//		else if (!ft_strcmp(str, tgetstr("kD", NULL)))
//		{
//			write(1, "hi", 2);
//		}
//tputs(tgetstr("dc", NULL), 1, myputchar);