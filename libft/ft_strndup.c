/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:26:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/04/18 09:55:11 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strnew(size_t size)
{
	char	*new;

	new = (char *)malloc(size + 1);
	if (!new)
		return (NULL);
	ft_bzero(new, size + 1);
	return (new);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_strnew(n);
	if (!str)
		return (NULL);
	str = ft_strncpy(str, s, n);
	return (str);
}
