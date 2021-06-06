#include "environment.h"

/*
** The getenv_from_lst() function searches the environment array to find the
** environment variable name, and returns a pointer to the corresponding value
** string. Returns NULL if there is no match. Exit if malloc problem.
*/

char	*getenv_from_lst(t_dlst *env, const char *name)
{
	size_t	len;
	t_dlst	*tmp_lst;
	char	*variable_value;

	if (!name || !env)
		return (NULL);
	tmp_lst = env;
	while (tmp_lst)
	{
		len = ft_strlen(name);
		if (!ft_strncmp(name, tmp_lst->str, len) && tmp_lst->str[len] == '=')
		{
			variable_value = ft_strdup(&tmp_lst->str[len + 1]);
			if (!variable_value)
				error_handler(NULL, ENOMEM);
			return (variable_value);
		}
		tmp_lst = tmp_lst->next;
	}
	return (NULL);
}

/*
** The set_environment() parses environment variables and values, the result is
** stored in a list of strings.
*/

void	set_environment(const char	*envp[], t_all *all)
{
	int		i;
	char	*tmp_str;

	i = -1;
	while (envp[++i])
	{
		tmp_str = ft_strdup(envp[i]);
		if (!tmp_str)
		{
			doubly_lst_clear(&all->env);
			error_handler(NULL, ENOMEM);
		}
		if (!doubly_lst_append(&all->env, doubly_lst_new(tmp_str)))
		{
			free(tmp_str);
			doubly_lst_clear(&all->env);
			error_handler(NULL, ENOMEM);
		}
	}
}
