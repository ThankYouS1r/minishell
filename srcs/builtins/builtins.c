#include "builtins.h"

int	builtins(t_dlst **ptr_token, t_all *all)
{
	if (!ft_strcmp(((*ptr_token))->str, "echo"))
		all->exit_status = echo_cmd(ptr_token, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "cd"))
		all->exit_status = cd_cmd(ptr_token, all->env);
	else if (!ft_strcmp((*ptr_token)->str, "pwd"))
		all->exit_status = pwd_cmd(ptr_token, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "export"))
		all->exit_status = export_cmd(ptr_token, all->env, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "unset"))
		all->exit_status = unset_cmd(ptr_token, all->env);
	else if (!ft_strcmp((*ptr_token)->str, "env"))
		all->exit_status = env_cmd(ptr_token, all->env, all->fd_out);
	else if (!ft_strcmp((*ptr_token)->str, "exit"))
		all->exit_status = exit_cmd(ptr_token, all->exit_status,
				&all->shell_history);
	else
		return (0);
	return (1);
}

int	is_valid_variable_name(char *variable_name, char end_char)
{
	int	i;

	i = 0;
	if (variable_name[0] != '_' && !ft_isalpha(variable_name[0]))
		return (0);
	while (variable_name[++i] && variable_name[i] != end_char)
	{
		if (variable_name[i] != '_' && !ft_isalnum(variable_name[i]))
			return (0);
	}
	return (1);
}
