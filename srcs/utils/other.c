/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 14:10:50 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 08:19:00 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	go_to_end_or_separator(t_dlst **ptr_token)
{
	while (*ptr_token && !is_separator(*ptr_token))
			*ptr_token = (*ptr_token)->next;
}
