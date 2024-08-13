/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:06:43 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/30 12:04:13 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

// char	*ft_strchr(const char *s, int c)
// {
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)s);
// 	else
// 		return (NULL);
// }