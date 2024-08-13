/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:35:27 by atoepper          #+#    #+#             */
/*   Updated: 2024/02/28 13:23:53 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putarg(const char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_printf(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr_printf(va_arg(args, char *)));
	if (c == 'p')
		return (ft_putptr_printf(va_arg(args, void *)));
	if (c == '%')
		return (ft_putchar_printf('%'));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_printf(va_arg(args, int)));
	if (c == 'u')
		return (ft_putuint_printf(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_puthexlow_printf(va_arg(args, int)));
	if (c == 'X')
		return (ft_puthexup_printf(va_arg(args, int)));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str != '%')
				count += ft_putarg(*str, args);
			else
				count += ft_putchar_printf('%');
		}
		else
		{
			count++;
			write(1, str, 1);
		}
		str++;
	}
	va_end(args);
	return (count);
}
