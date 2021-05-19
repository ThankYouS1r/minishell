/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:05:52 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 14:53:54 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcap_commands.h"

# define K_UP	"\e[A"
# define K_DOWN 	"\e[B"
# define K_CTRL_D "\4"
# define K_ENTER	"\10"

static int	ft_myputchar(int nb)
{
	return (write (1, &nb, 1));
}


struct termios ft_init_settings(void)
{
	int		check_get;
	struct termios term;
	struct termios saved_attributes;

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

void ft_save_str(char *str, t_parser *parse)
{
	int counter;

	counter = parse->count;
	if (counter == 1)
	{
		parse->str = ft_malloc(2);
		parse->str[0] = str[0];
		parse->str[1] = '\0';
	}
	else if (counter > 1)
	{
		parse->str = ft_realloc(parse->str, counter);
		parse->str[counter - 1] = str[0];
		parse->str[counter] = '\0';
	}
}


int	ft_parse_args(struct termios saved_attributes)
{
	char	str[1000];
	//char **temp;
	t_parser parse;
	ssize_t l;

	parse.count = 0;
	while (strcmp(str, K_CTRL_D)) //идти до CTRL + D(004 по терминалу)
	{
		tputs(tgetstr("sc", NULL), 1, ft_myputchar); //Сохранение позиции курсора
		l = read(0, str, 100);
		str[l] = 0;
		if (!strcmp(str, tgetstr("kb", NULL)) || !strcmp(str, "\177"))
		{
			if (parse.count > 0)
			{
				tputs(tgetstr("le", NULL), 1, ft_myputchar);
				tputs(tgetstr("dc", NULL), 1, ft_myputchar);
				parse.count--;
			}
		}
		else if (!ft_strncmp(str, K_UP, 3))
		{
			write(1, "UP", 2);
		}
		else if (!ft_strncmp(str, K_DOWN, 3))
		{
			write(1, "DOWN", 5);
		}
		else if (!strcmp(str, tgetstr("kD", NULL)))
			tputs(tgetstr("dc", NULL), 1, ft_myputchar);
		else if (*str == 10) //ENTER
		{
			//write(1, "\n", 1);
			//write(1, parse.str, ft_strlen(parse.str));
			//ft_parse_str
		}
		else
		{
			parse.count++;
			ft_save_str(str, &parse);
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
	saved_attributes = ft_init_settings();
	ft_parse_args(saved_attributes);

	return (0);
}