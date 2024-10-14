/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/14 11:51:13 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(char **argv, t_shell *mshell, int fd)
{
	(void)fd;
	if (argv[1] != NULL)
	{
		if (argv[2] != NULL)
			return (ft_set_error(mshell, 1, EXIT_ARG), 1);
		else
			mshell->exit_prog_val = ft_atoi(argv[1]);
	}
	else
		mshell->exit_prog_val = mshell->exit_status;
	mshell->is_exit_prog = TRUE;
	return (0);
}
