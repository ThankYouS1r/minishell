/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lst_delete_element.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 17:22:34 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 09:43:30 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	doubly_lst_delete_element(t_dlst **lst)
{
	if (*lst)
	{
		if ((*lst)->prev)
			(*lst)->prev->next = (*lst)->next;
		if ((*lst)->next)
			(*lst)->next->prev = (*lst)->prev;
		free((*lst)->str);
		(*lst)->str = NULL;
		free(*lst);
		*lst = NULL;
	}
}
