#include "parsing.h"

char	*read_line(void)
{
	char	ch;
	int		len;
	char	*line;
	ssize_t	ret;

	line = ft_strdup("");
	if (!line)
		error_handler(NULL, ENOMEM);
	len = 0;
	while (1)
	{
		ret = read(STDIN_FILENO, &ch, 1);
		if (ret < 0 && errno == EINTR)
			continue ;
		else if (ret < 0)
			return (NULL);
		if (!ret || ch == '\n')
			break ;
		line = ft_realloc(line, len + 2);
		if (!line)
			return (NULL);
		line[len] = ch;
		line[++len] = '\0';
	}
	return (line);
}
