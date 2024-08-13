/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:51:36 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/27 13:10:53 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	mem = malloc(count * size);
	if (mem != NULL)
		ft_memset(mem, 0, count * size);
	return (mem);
}
