/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 07:45:31 by alexander         #+#    #+#             */
/*   Updated: 2023/11/28 17:19:43 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_count_words(char *s, char c)
{
	int	count;
	int	word;

	if (*s == '\0')
		return (0);
	count = 0;
	word = 0;
	while (*s != '\0')
	{
		if (*s == c && word == 1)
			word = 0;
		if (*s != c && word == 0)
		{
			word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static int	ft_nextlen(char *s, char c)
{
	char	*pt;
	int		count;

	pt = s;
	count = 0;
	while (*pt != c && *pt != '\0')
	{
		count++;
		pt++;
	}
	return (count);
}

static char	**ft_clone(char *s, char **arr, char c, int elem)
{
	int	i;
	int	len;

	i = 0;
	while (i < elem)
	{
		len = ft_nextlen(s, c);
		while (len == 0)
		{
			s++;
			len = ft_nextlen(s, c);
		}
		arr[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (arr[i] == NULL)
			return (NULL);
		ft_strlcpy(arr[i], s, len + 1);
		s += len;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void	ft_free_arr(char **arr, int len)
{
	while (len > 0)
	{
		free(arr[len - 1]);
		len--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	char	*pt;
	char	**arr;
	int		elements;

	pt = (char *)s;
	elements = ft_count_words(pt, c);
	arr = (char **)malloc(sizeof(char *) * (elements + 1));
	if (arr == NULL)
		return (NULL);
	if (ft_clone(pt, arr, c, elements) == NULL)
	{
		ft_free_arr(arr, elements + 1);
		return (NULL);
	}
	return (arr);
}
