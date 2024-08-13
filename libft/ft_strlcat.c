/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:30:49 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/28 14:20:55 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*pt;
	size_t	dest_len;
	size_t	src_len;
	size_t	result;
	size_t	i;

	pt = (char *)src;
	src_len = ft_strlen(pt);
	dest_len = ft_strlen(dst);
	result = 0;
	i = 0;
	if (dstsize > dest_len)
		result = src_len + dest_len;
	else
		result = dstsize + src_len;
	while (pt[i] && (dest_len + 1) < dstsize)
	{
		dst[dest_len] = pt[i];
		dest_len++;
		i++;
	}
	dst[dest_len] = '\0';
	return (result);
}

// size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	if (dstsize == 0)
// 		return (ft_strlen(src));
// 	if ((int)dstsize <= ft_strlen(dst))
// 		return (dstsize + ft_strlen(src));
// 	while (i < dstsize && dst[i])
// 		i++;
// 	while (src[j] && i + j + 1 < dstsize)
// 	{
// 		dst[i + j] = src[j];
// 		j++;
// 	}
// 	dst[i + j] = '\0';
// 	return (i + ft_strlen(src));