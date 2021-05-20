/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:04:08 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/20 09:27:16 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handlers.h"



int	error_handler(const char *message, int error_code)
{
	ft_putstr_fd(RED_COLOR, STDERR_FILENO);
	ft_putstr_fd("minishell-> ", STDERR_FILENO);
	if (!message)
		message = strerror(error_code);
	ft_putendl_fd((char *)message, STDERR_FILENO);
	ft_putstr_fd(NONE_COLOR, STDERR_FILENO);
	if (error_code == ENOMEM)
		exit(error_code);
	return (error_code);
}