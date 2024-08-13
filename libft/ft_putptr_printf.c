/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:19:23 by atoepper          #+#    #+#             */
/*   Updated: 2024/01/19 11:52:44 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptrlen(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

static void	ft_putadress(uintptr_t num)
{
	if (num >= 16)
	{
		ft_putadress(num / 16);
		ft_putadress(num % 16);
	}
	else
	{
		if (num < 10)
			ft_putchar_printf (num + '0');
		else
			ft_putchar_printf (num - 10 + 'a');
	}
}

int	ft_putptr_printf(void *arg)
{
	if (arg == NULL)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write (1, "0x", 2);
	ft_putadress((uintptr_t)arg);
	return (ft_ptrlen((uintptr_t)arg) + 2);
}
