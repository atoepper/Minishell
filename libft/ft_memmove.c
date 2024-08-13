/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:03 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/21 17:18:02 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;

	if (dst == NULL && src == NULL)
		return (dst);
	if (dst > src && dst + len > src)
	{
		i = len ;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((const char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	return (dst);
}
