/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/11 13:09:49 by atoepper         ###   ########.fr       */
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
		mshell->exit_prog_val = 0;
	mshell->is_exit_prog = TRUE;
	return (0);
}
