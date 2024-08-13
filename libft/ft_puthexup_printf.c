/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexup_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:50:47 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/19 11:49:34 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hexlen(unsigned int nbr)
{
	int	len;

	len = 1;
	if (nbr < 0)
		len++;
	while (nbr / 16 != 0)
	{
		nbr /= 16;
		len++;
	}
	return (len);
}

static void	ft_puthex(unsigned int nbr, char *s)
{
	if (nbr >= 16)
		ft_puthex(nbr / 16, s);
	ft_putchar_printf(s[nbr % 16]);
}

int	ft_puthexup_printf(unsigned int nbr)
{
	ft_puthex(nbr, "0123456789ABCDEF");
	return (ft_hexlen(nbr));
}
