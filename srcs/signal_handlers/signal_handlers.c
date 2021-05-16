/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:55:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/16 23:55:49 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"

void	handle_sigint(int code)
{
	(void)code;
}

void	handle_sigquit(int code)
{
	(void)code;
}


void	set_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
