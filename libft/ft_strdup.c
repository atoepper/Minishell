/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:05:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/30 12:08:04 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dupl;

	dupl = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (dupl == NULL)
		return (NULL);
	ft_strlcpy(dupl, s1, ft_strlen((char *)s1) + 1);
	return (dupl);
}
