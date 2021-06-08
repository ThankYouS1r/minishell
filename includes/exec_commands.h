#ifndef EXEC_COMMANDS_H
# define EXEC_COMMANDS_H

# include "environment.h"
# include "utils.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

int		external_programs(t_dlst **ptr_token, t_all *all);
char	**make_array_from_lst(t_dlst *head);
char	**make_arg_array_from_lst(t_dlst *head, int operator);
void	clear_array(char **str);
char	*find_path(t_dlst *ptr_token, char *path_lst);

#endif
