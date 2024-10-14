/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/14 17:37:19 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int is_numeric(char *str)
{
	while (*str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if(!ft_isdigit(*str))
			return(0);
		else
			str++;
	}
	return (1);
}


int	ft_exit(char **argv, t_shell *mshell, int fd)
{
	(void)fd;
	if (argv[1] != NULL)
	{
		if (!is_numeric(argv[1]) || (ft_strlen(argv[1]) > 19 || ft_atoi(argv[1]) < 0))
		{
			mshell->exit_prog_val = 2;
			mshell->is_exit_prog = TRUE;
			return (ft_set_error(mshell, 1, EXIT_ARG_NUM), 2);
		}
		else
		{		
			if (argv[2] != NULL)
				return (ft_set_error(mshell, 1, EXIT_ARG), 1);
			else
				mshell->exit_prog_val = ft_atoi(argv[1]);
		}
	}
	else
		mshell->exit_prog_val = mshell->exit_status;
	mshell->is_exit_prog = TRUE;
	return (0);
}
