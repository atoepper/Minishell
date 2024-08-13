/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:33:50 by alexander         #+#    #+#             */
/*   Updated: 2024/01/30 12:05:04 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*pt;
	char	*appl;
	size_t	i;

	i = 0;
	pt = (char *)s;
	if (pt == NULL)
		return (NULL);
	appl = (char *)malloc(sizeof(char) * (ft_strlen(pt) + 1));
	if (appl == NULL)
		return (NULL);
	while (i < ft_strlen(pt))
	{
		appl[i] = f(i, pt[i]);
		i++;
	}
	appl[i] = '\0';
	return (appl);
}
