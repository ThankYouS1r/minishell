#include "exec_commands.h"

void	clear_array(char **str)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

char	**make_array_from_lst(t_dlst *head)
{
	char	**array;
	t_dlst	*tmp;
	int		i;

	array = (char **)ft_calloc(doubly_lst_size(head) + 1, sizeof(char *));
	if (!array)
		error_handler(NULL, ENOMEM);
	tmp = head;
	i = -1;
	while (tmp)
	{
		array[++i] = ft_strdup(tmp->str);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			array = NULL;
			error_handler(NULL, ENOMEM);
		}
		tmp = tmp->next;
	}
	return (array);
}


char	**make_arg_array_from_lst(t_dlst *head)
{
	char	**array;
	t_dlst	*tmp;
	int		i;

	i = 0;
	tmp = head;
	while (tmp && !is_separator(tmp->str))
	{
		tmp = tmp->next;
		i++;
	}
	array = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!array)
		error_handler(NULL, ENOMEM);
	tmp = head;
	i = -1;
	while (tmp && !is_separator(tmp->str))
	{
		array[++i] = ft_strdup(tmp->str);
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			free(array);
			array = NULL;
			error_handler(NULL, ENOMEM);
		}
		tmp = tmp->next;
	}
	return (array);
}
