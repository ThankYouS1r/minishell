/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:04:08 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 11:22:49 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handlers.h"

int	error_handler(const char *message, int error_code)
{
	write(2, "minishell: ", 11);
	if (!message)
		message = strerror(error_code);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);

	if (error_code == ENOMEM)
		exit(error_code);
	return (error_code);
}