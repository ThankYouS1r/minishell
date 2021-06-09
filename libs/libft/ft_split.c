/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eluceon <eluceon@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:34:54 by eluceon           #+#    #+#             */
/*   Updated: 2021/04/25 22:11:31 by eluceon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	words(char const *s, char c)
{
	int	qty;
	int	i;

	qty = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			qty++;
			i++;
		}
		while (s[i] != c && s[i])
			i++;
	}
	return (qty);
}

static char	*ft_subnstr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if (i < start)
	{
		if (!(substring = (char *)malloc(sizeof(char))))
			return (NULL);
		substring[0] = '\0';
		return (substring);
	}
	if (!(substring = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		start;
	int		i;
	int		j;

	strs = (char **)malloc(sizeof(char *) * (words(s, c) + 1));
	if (!s || !strs)
		return (NULL);
	start = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if ((i > start) && (!(strs[j++] = ft_subnstr(s, start, i - start))))
		{
			free_strs(strs);
			return (NULL);
		}
	}
	strs[j] = NULL;
	return (strs);
}
