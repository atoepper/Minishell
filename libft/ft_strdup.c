/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:05:36 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/15 10:34:19 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dupl;

	if (s1 == NULL)
		return (NULL);
	dupl = (char *)malloc(ft_strlen((char *)s1) + 1);
	if (dupl == NULL)
		return (NULL);
	ft_strlcpy(dupl, s1, ft_strlen((char *)s1) + 1);
	return (dupl);
}
