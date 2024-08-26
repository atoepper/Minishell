/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:35:06 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 15:41:12 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_exit(char **argv, char **envp)
{
	int	exitvalue;

	((void)argv, (void)envp);
	exitvalue = 0;
	exit(exitvalue);
}
