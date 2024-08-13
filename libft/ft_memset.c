/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:55:25 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/20 13:16:27 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pt;
	size_t			i;

	i = 0;
	pt = b;
	while (i < len)
	{
		pt[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
