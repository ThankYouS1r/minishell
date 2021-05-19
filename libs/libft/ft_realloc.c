#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*newptr;

	newptr = ft_malloc(size);
	if (!newptr)
	{
		if (ptr)
			free(ptr);
		return (0);
	}
	if (ptr)
	{
		ft_memmove(newptr, ptr, size);
		free(ptr);
	}
	return (newptr);
}
