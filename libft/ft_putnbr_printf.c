/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:34:53 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/19 11:52:06 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int nbr)
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

static void	ft_putnbr(int nbr)
{
	if (nbr == INT_MIN)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar_printf('-');
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr(nbr / 10);
	ft_putchar_printf(nbr % 10 + '0');
}

int	ft_putnbr_printf(int nbr)
{
	ft_putnbr(nbr);
	return (ft_numlen(nbr));
}
