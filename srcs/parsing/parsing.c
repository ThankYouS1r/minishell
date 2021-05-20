#include "parsing.h"

t_doubly_lst	*parsing(t_doubly_lst	*token_lst)
{
	char			*line;
	ssize_t			i;
	char			*tmp;

	tmp = NULL;
	token_lst = NULL;
	line = read_line();
	i = -1;
	while (line[++i])
	{
		if (!is_spec_symbols(line[i]) && !ft_iswhitespace(line[i]))
		{
			tmp = str_join_char(tmp, line[i]);
			if (!tmp)
			{
				doubly_lst_clear(&token_lst);
				error_handler(NULL, ENOMEM);
			}
		}
		if ((tmp && ft_iswhitespace(line[i])) || (tmp && line[i + 1] == 0))
		{
			if (!(doubly_lst_append(&token_lst, doubly_lst_new(tmp))))
			{
				doubly_lst_clear(&token_lst);
				error_handler(NULL, ENOMEM);
			}
			tmp = NULL;
		}
		// else if (ft_iswhitespace(line[i]))
		// 	++i;
	}
	return (token_lst);
}
