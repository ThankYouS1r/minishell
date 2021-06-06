/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:15:22 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 09:43:30 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_minishell_history(t_dlst **ptr_history, int direction)
{
	if (direction == PREVIOUS_HISTORY && *ptr_history && (*ptr_history)->prev)
	{
		(*ptr_history) = (*ptr_history)->prev;
	//ft_putstr_fd((*ptr_history)->str, STDIN_FILENO);
	}
	else if (direction == NEXT_HISTORY && *ptr_history && (*ptr_history)->next)
	{
		(*ptr_history) = (*ptr_history)->next;
		//ft_putstr_fd((*ptr_history)->str, STDIN_FILENO);
	}
}

void	add_history_to_lst(char *str, t_dlst **head, t_dlst **p_history)
{
	if (!doubly_lst_append(head, doubly_lst_new(str)))
		error_handler(NULL, ENOMEM);
	*p_history = *head;
	while (*p_history && (*p_history)->next)
		*p_history = (*p_history)->next;
}

void	write_to_lst(t_dlst **head, t_dlst **p_history, int fd, char **line)
{
	int	ret;

	while (1)
	{
		ret = read_line(fd, line);
		if (ret < 0)
		{
			error_handler(NULL, errno);
			exit(errno);
		}
		if (!doubly_lst_append(head, doubly_lst_new(*line)))
			error_handler(NULL, ENOMEM);
		if (ret == 0)
			break ;
	}
	*p_history = *head;
	while (*p_history && (*p_history)->next)
		*p_history = (*p_history)->next;
}

void	open_history_file(t_dlst **head_history, t_dlst **ptr_history)
{
	int		fd;
	char	*line;

	fd = open("./minishell_history", O_RDONLY);
	if (fd == -1)
		error_handler(NULL, errno);
	else
	{
		write_to_lst(head_history, ptr_history, fd, &line);
		close(fd);
	}
}

void save_history_to_file_and_close(t_dlst **head_history)
{
	t_dlst	*tmp;
	int		fd;

	fd = open("./minishell_history", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd > -1)
	{
		tmp = *head_history;
		while (tmp)
		{
			write(fd, tmp->str, ft_strlen(tmp->str));
			if (tmp->next)
				write(fd, "\n", 1);
			tmp = tmp->next;
		}
		close(fd);
	}
	doubly_lst_clear(head_history);
}
