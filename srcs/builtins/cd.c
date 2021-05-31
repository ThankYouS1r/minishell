/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 09:20:44 by eluceon           #+#    #+#             */
/*   Updated: 2021/05/31 16:21:21 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	go_home(t_dlst *env)
{
	char	*home;
	int		ret;

	home = getenv_from_array(env, "HOME");
	if (!home)
	{
		cmd_error_message("cd", NULL, "HOME not set");
		return (ERROR);
	}
	ret = chdir(home);
	free(home);
	if (ret)
	{
		cmd_error_message("cd", NULL, strerror(errno));
		return (errno);
	}
	return (SUCCESS);
}

int	go_path(t_dlst **ptr_token)
{
	int	ret;

	ret = chdir((*ptr_token)->str);
	go_to_end_or_separator(ptr_token);
	if (ret)
	{
		cmd_error_message("cd", NULL, strerror(errno));
		return (errno);
	}
	return (SUCCESS);
}

int	change_environment(t_dlst **env, char *name, char *value)
{
	char	*new_str;
	t_dlst	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->str, ft_strlen(name)))
		{
			new_str = ft_strjoin(name, value);
			if (!new_str)
				error_handler(NULL, ENOMEM);
			free(tmp->str);
			tmp->str = new_str;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int change_pwd(char *oldpwd, t_dlst **env)
{
	char	*cwd;
	int		status;

	status = SUCCESS;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cmd_error_message("pwd", NULL, strerror(errno));
		status = errno;
	}
	else
	{
		status = change_environment(env, "PWD=", cwd);
		free(cwd);
	}
	status += change_environment(env, "OLDPWD=", oldpwd);
	return (status);
}

int	cd_cmd(t_dlst **ptr_token, t_dlst *env)
{
	char	*oldpwd;
	int		status;

	*ptr_token = (*ptr_token)->next;
	if ((*ptr_token) && (*ptr_token)->next && !is_separator((*ptr_token)->next->str))
	{
		cmd_error_message("cd", NULL, "too many arguments");
		go_to_end_or_separator(ptr_token);
		return (ERROR);
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		cmd_error_message("cd", NULL, strerror(errno));
		go_to_end_or_separator(ptr_token);
		return (errno);
	}
	status = 0;
	if (*ptr_token && !is_separator((*ptr_token)->str))
		status = go_path(ptr_token);
	else if (!*ptr_token || is_separator((*ptr_token)->str))
		status = go_home(env);
	if (!status)
		change_pwd(oldpwd, &env);
	free(oldpwd);
	return (status);
}
