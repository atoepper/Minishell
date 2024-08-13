/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:47:18 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/30 12:09:14 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	length;

	length = (size_t)ft_strlen((char *)s);
	if (s == NULL)
		return (NULL);
	if ((size_t)start >= length)
	{
		sub = (char *)malloc(sizeof(char));
		*sub = '\0';
		return (sub);
	}
	if (len > length)
		len = length;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
