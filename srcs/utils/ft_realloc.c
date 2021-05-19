/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 10:27:47 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 10:41:28 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	
	if (ptr && size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = (char *)malloc(size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (new_ptr);
	new_ptr = ft_memmove(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}