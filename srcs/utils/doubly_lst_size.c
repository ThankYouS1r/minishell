/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doubly_lst_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:35:24 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/06 09:43:30 by lmellos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	doubly_lst_size(t_dlst *lst)
{
	int		size;
	t_dlst	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}
