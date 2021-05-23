# include "utils.h"

void	free_doble_array(char **array)
{
	int	i;
	int	j;

	i = -1;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
		{
			free(array[i]);
			array[i] = NULL;
		}
	}
	free(array);
	array = NULL;
}

int	free_all_exit(t_all *all, char *line, int error_code)
{
	if (all->env.array)
		free_doble_array(all->env.array);
	if (all->lst_token)
		doubly_lst_clear(&all->lst_token);
	if (line)
	{
		free(line);
		line = NULL;
	}
	if (error_code)
		exit (error_code);
	return (0);
}
