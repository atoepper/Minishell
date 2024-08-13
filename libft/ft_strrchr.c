/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:17:29 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/27 13:14:16 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_occ;

	last_occ = NULL;
	while (*s)
	{
		if (*s == (char)c)
			last_occ = s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)last_occ);
}
