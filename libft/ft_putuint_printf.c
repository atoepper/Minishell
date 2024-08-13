/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_printf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:41:42 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/19 11:50:11 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(unsigned int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
		len++;
	while (nbr / 10 != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static void	ft_putuint(unsigned int nbr)
{
	if (nbr >= 10)
		ft_putuint(nbr / 10);
	ft_putchar_printf(nbr % 10 + '0');
}

int	ft_putuint_printf(unsigned int nbr)
{
	ft_putuint(nbr);
	return (ft_numlen(nbr));
}
