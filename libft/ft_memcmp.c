/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:37:20 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/27 13:12:29 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*pt1;
	unsigned char	*pt2;

	pt1 = (unsigned char *)s1;
	pt2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*pt1 != *pt2)
			return (*pt1 - *pt2);
		pt1++;
		pt2++;
		n--;
	}
	return (0);
}
