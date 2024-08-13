/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:53:44 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/19 13:55:02 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *src, size_t size)
{
	void	*dest;

	dest = malloc(size);
	if (dest != NULL)
		ft_memcpy(dest, src, size);
	return (dest);
}
