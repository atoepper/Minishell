/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/27 13:50:48 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(char **argv, t_env *envlst)
{
	int	exitvalue;

	(void)envlst;
	exitvalue = 0;
	if (argv[1] != NULL)
		if (argv[2] != NULL)
			return (perror("exit: too many arguments"), 1);
	if (argv[1] != NULL)
		exitvalue = ft_atoi(argv[1]);
	exit(exitvalue);
}
