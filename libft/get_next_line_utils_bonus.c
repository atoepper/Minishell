/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:02:38 by atoepper          #+#    #+#             */
/*   Updated: 2024/03/25 17:37:55 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* size_t	ft_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c] != '\0')
		c++;
	return (c);
} */

size_t	ft_linelen(char *str)
{
	size_t	count;

	count = 0;
	while (*str && *str != '\n')
	{
		str++;
		count++;
	}
	return (count);
}

void	copy_line(char *line, char *text_read)
{
	int	i;

	i = 0;
	while (text_read[i] && text_read[i] != '\n')
	{
		line[i] = text_read[i];
		i++;
	}
	if (text_read[i] == '\n')
	{
		line[i] = text_read[i];
		i++;
	}
	line[i] = '\0';
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (join == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			join[i] = s1[i];
	while (s2[j] != '\0')
		join[i++] = s2[j++];
	join[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (join);
}
