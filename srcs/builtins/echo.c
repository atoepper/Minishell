/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:29:53 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/17 15:11:28 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_echo(char **argv, t_shell *mshell, int fd)
{
	int	i;
	int	return_val;

	(void)mshell;
	i = 1;
	if (argv == NULL || argv[1] == NULL)
		return (0);
	if (ft_strncmp(argv[1], "-n", 3) == 0)
		i++;
	if (argv[i] != NULL)
	{
		return_val = write(fd, argv[i], ft_strlen(argv[i]));
		i++;
	}
	while (argv[i] != NULL)
	{
		return_val = write(fd, " ", 1);
		return_val = write(fd, argv[i], ft_strlen(argv[i]));
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3) != 0)
		return_val = write(fd, "\n", 1);
	return_val++;
	return (0);
}
