/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/03 16:07:33 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(char **argv, t_shell *mshell)
{
	int	exitvalue;

	(void)mshell;
	exitvalue = 0;
	if (argv[1] != NULL)
		if (argv[2] != NULL)
			return (perror("exit: too many arguments"), 1);
	if (argv[1] != NULL)
		exitvalue = ft_atoi(argv[1]);
	exit(exitvalue);
}
