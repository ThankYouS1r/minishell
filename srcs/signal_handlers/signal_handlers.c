/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:55:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/27 19:48:59 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"

void	handle_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("Testing sigint", STDERR_FILENO); // TMP
}

void	handle_sigquit(int signum)
{
	(void)signum;
	ft_putstr_fd("Testing sigquit", STDERR_FILENO); // TMP
}


void	set_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
