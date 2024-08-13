/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:14:36 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/20 13:16:12 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*pt;
	size_t				i;

	pt = s;
	i = 0;
	while (i < n)
	{
		if (pt[i] == (unsigned char)c)
			return ((void *)s);
		s++;
		i++;
	}
	return (NULL);
}
