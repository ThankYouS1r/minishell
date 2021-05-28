 #include "builtins.h"


int		execute_builtin(t_dlst **ptr_token, t_all *all)
{
	int		status;

	(void)all; //TMP! DELETE ME!!!!!!!
	status = 0;
	if (!ft_strncmp(((*ptr_token))->str, "echo", 5))
		status = echo_cmd(ptr_token);
	// else if (!ft_strcmp((*ptr_token)->str, "cd"))
	// 	status = cd_cmd(ptr_token, all->env);
	// else if (!ft_strcmp(ptr_token, "pwd"))
	// 	status = pwd_cmd();
	// else if (!ft_strcmp((*ptr_token)->str, "export"))
	// 	status = export_cmd(ptr_token, all->env, all->secret_env);
	// else if (!ft_strcmp((*ptr_token)->str, "unset"))
	// 	status = unset_cmd(ptr_token, all);
	// else if (!ft_strcmp((*ptr_token)->str, "env"))
	// 	status = env_cmd(all->env);
	return (status);
}
