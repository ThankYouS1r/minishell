/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 09:29:43 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/16 23:25:40 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"

typedef struct s_env
{
	// More data will be added later!
	size_t		nbr_variables;
}				t_evp;


t_evp *set_environment(const char *envp[]);

#endif
