/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:03:44 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 12:53:47 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*read_line()
{
	char	ch;
	int		len;
	char	*line;

	line = ft_strdup("\0");
	if (!line)
		error_handler(NULL, ENOMEM);
	len = 0;
	while (read(STDIN_FILENO, &ch, 1) && ch != '\n')
	{
		line = ft_realloc(line, len + 2);
		if (!line)
			error_handler(NULL, ENOMEM);
		line[len] = ch;
		line[++len] = '\0';
	}
	return (line);
}