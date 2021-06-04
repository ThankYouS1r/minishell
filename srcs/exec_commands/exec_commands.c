/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:57:25 by eluceon           #+#    #+#             */
/*   Updated: 2021/06/04 15:32:28 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_commands.h"

int	find_file_in_dir(const char *path, const char *file)
{
	struct dirent	*entry;
	int				ret;
	DIR				*dirp;

	ret = 0;
	dirp = opendir(path);
	if (!dirp)
		return (0);
	errno = 0;
	while (1)
	{
		entry = readdir(dirp);
		if (!entry)
			break ;
		if (!ft_strcmp(entry->d_name, file))
		{
			ret = 1;
			break ;
		}
	}
	if (errno && !entry)
		error_handler(NULL, errno);
	closedir(dirp);
	return (ret);
}

void	make_full_cmd_name(char **path, char *file)
{
	int		len;
	char	*full_file_name;

	len = ft_strlen(*path) + ft_strlen(file) + 2;
	full_file_name = (char *)malloc(len * sizeof(char));
	if (!full_file_name)
		error_handler(NULL, ENOMEM);
	ft_strlcpy(full_file_name, *path, len);
	ft_strlcat(full_file_name, "/", len);
	ft_strlcat(full_file_name, file, len);
	free(*path);
	*path = full_file_name;
}

char	*find_path(t_dlst *ptr_token, char *path_lst)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (j < 0 || path_lst[j])
	{
		i = ++j;
		while (path_lst[j] && path_lst[j] != ':')
			j++;
		path = ft_substr(path_lst, i, j - i);
		if (!path)
			error_handler(NULL, ENOMEM);
		if (find_file_in_dir(path, ptr_token->str))
		{
			make_full_cmd_name(&path, ptr_token->str);
			return (path);
		}
		free(path);
	}
	return (NULL);
}

void	run_program(t_dlst **ptr_token, t_all *all, char *path)
{
	char	**arg_array;
	char	**envp_array;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		error_handler(NULL, errno);
	if (!pid)
	{
		arg_array = make_arg_array_from_lst(*ptr_token);
		envp_array = make_array_from_lst(all->env);
		status = execve(path, arg_array, envp_array);
		cmd_error_message((*ptr_token)->str, NULL, "Problem with execution");
		clear_array(arg_array);
		clear_array(envp_array);
		exit(status);
	}
	waitpid(pid, NULL, 0);
}

int	execute_program(t_dlst **ptr_token, t_all *all)
{
	char		*path;
	char		*path_lst;
	struct stat	s_stat;

	if (!stat((*ptr_token)->str, &s_stat))
		run_program(ptr_token, all, (*ptr_token)->str);
	else
	{
		path_lst = getenv_from_lst(all->env, "PATH");
		if (!path_lst)
			return (0);
		path = find_path(*ptr_token, path_lst);
		free(path_lst);
		if (!path)
			return (0);
		run_program(ptr_token, all, path);
		free(path);
	}
	go_to_end_or_separator(ptr_token);
	return (1);
}
