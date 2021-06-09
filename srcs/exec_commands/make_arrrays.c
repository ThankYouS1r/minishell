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

char	**fill_arg_array(t_dlst *head, int len, char ***array)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (is_separator(head) == REDIRECT_INPUT
			|| is_separator(head) == REDIRECT_OUTPUT
			|| is_separator(head) == APPEND_REDIRECT_OUTPUT)
			head = head->next->next;
		(*array)[i] = ft_strdup(head->str);
		if (!(*array)[i])
		{
			while (--i >= 0)
				free((*array)[i]);
			free(*array);
			(*array) = NULL;
			error_handler(NULL, ENOMEM);
		}
		head = head->next;
	}
	return (*array);
}

char	**make_arg_array_from_lst(t_dlst *head, int operator)
{
	char	**array;
	t_dlst	*tmp;
	int		len;
	int		nbr_redirections;

	len = 0;
	tmp = head;
	nbr_redirections = 0;
	while (tmp)
	{
		if ((operator == REDIRECT_INPUT || operator == REDIRECT_OUTPUT
			|| operator == APPEND_REDIRECT_OUTPUT)
			&& (operator == is_separator(tmp)) && nbr_redirections == 0)
		{
			nbr_redirections++;
			tmp = tmp->next->next;
		}
		if (!tmp || is_separator(tmp))
			break ;
		len++;
		tmp = tmp->next;
	}
	array = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!array)
		error_handler(NULL, ENOMEM);
	return(fill_arg_array(head, len, &array));
}
