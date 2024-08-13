/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:57:01 by atoepper          #+#    #+#             */
/*   Updated: 2023/11/27 13:10:36 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static void	put_digit(char *nbr, long n)
{
	int	i;
	int	sign;

	i = count_digits(n);
	if (n < 0)
	{
		sign = -1;
		n *= -1;
	}
	nbr[i] = '\0';
	i--;
	while (i >= 0)
	{
		nbr[i] = n % 10 + '0';
		n /= 10;
		if (i == 0 && sign == -1)
			nbr[i] = '-';
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;

	nbr = (char *)malloc(sizeof(char) * (count_digits(n) + 1));
	if (nbr == NULL)
		return (NULL);
	put_digit(nbr, n);
	return (nbr);
}
