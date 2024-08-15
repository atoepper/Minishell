/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uebergabe_Funktoin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:54:21 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 12:54:28 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	echo(int nb)
{
	return (nb);
}

int	ft_echo(int (*f)(int), int nb)
{
	return((*f)(nb));
}

int	main(void)
{
	printf("%i", ft_echo(&echo, 5));
	return (0);
}
