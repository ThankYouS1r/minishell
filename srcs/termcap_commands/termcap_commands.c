#include "termcap_commands.h"

static int	ft_myputchar(int nb)
{
	return (write (1, &nb, 1));
}

struct termios ft_init_settings(void)
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

char  *ft_save_str(char *str, char *struct_str, int counter)
{
	if (counter == 1)
	{
		struct_str = ft_malloc(2);
		struct_str[0] = str[0];
		struct_str[1] = '\0';
	}
	else if (counter > 1)
	{
		struct_str = ft_realloc(struct_str, counter);
		struct_str[counter - 1] = str[0];
		struct_str[counter] = '\0';
	}
	return (struct_str);
}

int	ft_escape_press(int count)
{
	if (count > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_myputchar);
		tputs(tgetstr("dc", NULL), 1, ft_myputchar);
		count--;
	}
	return (count);
}

int	ft_parse_args(struct termios saved_attributes)
{
	char		str[1000];
	t_termcap	termcap;
	ssize_t		l;

	termcap.count = 0;
	while (strcmp(str, K_CTRL_D) && strcmp(str, "\n")) //идти до CTRL + D(004 по терминалу)
	{
		tputs(tgetstr("sc", NULL), 1, ft_myputchar); //Сохранение позиции курсора
		l = read(0, str, 100);
		str[l] = 0;
		if (!strcmp(str, tgetstr("kb", NULL)) || !strcmp(str, "\177"))
			termcap.count = ft_escape_press(termcap.count);
		else if (!ft_strncmp(str, K_UP, 3))
		{
			write(1, "up", 2);
			//			history_check(arguments, flag for argument(1 up, 2 for down);
		}
		else if (!ft_strncmp(str, K_DOWN, 3))
		{
			write(1, "down", 4);
			//			history_check(arguments, flag for argument(1 up, 2 for down);
		}
		else if (!strcmp(str, tgetstr("kD", NULL)))
			tputs(tgetstr("dc", NULL), 1, ft_myputchar);
		// else if (*str == 10) //ENTER
		// {
		// 	//write(1, "\n", 1);
		// 	//write(1, parse.str, ft_strlen(parse.str));
		// 	//ft_parse_str
		// }
		else
		{
			termcap.count++;
			termcap.str = ft_save_str(str, termcap.str, termcap.count);
			write (1, str, l);
		}
	}
	write (1, "\n", 1);
	tcsetattr(0, TCSANOW, &saved_attributes);
	return (0);
}

int	termcap_start(void)
{
	struct termios saved_attributes;

	write (1, "\033[0;32mminishell->", 18);
	write (1, "\033[0;0m", 6);
	saved_attributes = ft_init_settings();
	ft_parse_args(saved_attributes);

	return (0);
}
