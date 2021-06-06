/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrdima <mrdima@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:59:38 by mrdima            #+#    #+#             */
/*   Updated: 2021/06/06 16:25:21 by mrdima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    close_fds(t_all *all)
{
    if (all->fd_in != STDIN_FILENO)
    {
        close(all->fd_in);
        all->fd_in = STDIN_FILENO;
    }
    if (all->fd_out != STDOUT_FILENO)
    {
        close(all->fd_out);
        all->fd_out = STDOUT_FILENO;
    }
}
