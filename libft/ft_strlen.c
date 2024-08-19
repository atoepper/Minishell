/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:53:26 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/19 11:06:21 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(char *str)
{
	size_t	count;

	count = 0;
	while (str != NULL && *str)
	{
		str++;
		count++;
	}
	return (count);
}
