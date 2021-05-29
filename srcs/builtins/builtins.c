 #include "builtins.h"

int		execute_builtin(t_dlst **ptr_token, t_all *all)
{
	if (!ft_strncmp(((*ptr_token))->str, "echo", ft_strlen("echo")))
		all->exit_status = echo_cmd(ptr_token);
	// else if (!ft_strncmp((*ptr_token)->str, "cd"))
	// 	all->exit_status = cd_cmd(ptr_token, all->env);
	else if (!ft_strncmp((*ptr_token)->str, "pwd", ft_strlen("pwd")))
		all->exit_status = pwd_cmd(ptr_token);
	// else if (!ft_strncmp((*ptr_token)->str, "export"))
	// 	all->exit_status = export_cmd(ptr_token, all->env, all->secret_env);
	else if (!ft_strncmp((*ptr_token)->str, "unset", ft_strlen("unset")))
	  	all->exit_status = unset_cmd(ptr_token, all->lst_env);
	else if (!ft_strncmp((*ptr_token)->str, "env", ft_strlen("env")))
		all->exit_status = env_cmd(ptr_token, all->lst_env);
	return (all->exit_status);
}
