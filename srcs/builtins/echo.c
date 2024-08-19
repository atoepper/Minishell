/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:29:53 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 16:06:50 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_echo(char **argv)
{
	int		i;

	i = 1;
	if (argv == NULL || argv[1] == NULL)
		return (0);
	if (ft_strncmp(argv[1], "-n\0", 3) == 0)
		i++;
	if (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		i++;
	}
	while (argv[i] != NULL)
	{
		printf(" %s", argv[i]);
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3) != 0)
		printf("\n");
	return (0);
}
