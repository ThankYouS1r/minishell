/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:59:11 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 14:32:57 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

char	**duplicate_string_array(const char *str_array[], size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	ft_crash(const char *str);
void	*ft_malloc(size_t size);

#endif
