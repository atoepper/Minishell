/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 10:47:54 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(char **argv, t_shell *mshell)
{
	int	exitvalue;

	(void)mshell;
	exitvalue = 0;
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
			return (perror("exit: too many arguments"), 1);
		exitvalue = ft_atoi(argv[1]);
	}
	mshell->is_exit_prog = TRUE;
	mshell->exit_prog_val = exitvalue;
	return (0);
}
