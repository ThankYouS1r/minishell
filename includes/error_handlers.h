/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:03:33 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/19 11:50:04 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLERS_H
# define ERROR_HANDLERS_H

# include <errno.h>
# include "libft.h"

int	error_handler(const char *message, int error_code);

#endif