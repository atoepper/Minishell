/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:18:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/30 12:09:01 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*trim;
	unsigned int	start;
	unsigned int	end;

	if (*s1 == '\0')
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen((char *)s1);
	if (*set != '\0')
	{
		while (ft_strchr((char *)set, s1[start]) != NULL && s1[start])
			start++;
		while (ft_strchr((char *)set, s1[end - 1]) != NULL && end - 1 > start)
			end--;
	}
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, s1 + start, end - start + 1);
	return (trim);
}
