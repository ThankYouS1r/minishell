/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:55:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/16 09:16:23 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"

void	handle_sigint(void)
{

}

void	handle_sigquit(void)
{

}


void	set_signal_handlers(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
}
