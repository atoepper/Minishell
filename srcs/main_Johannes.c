/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Johannes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/27 14:56:36 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	char	*argvs[][6] = {
		{"echo", "test", NULL},
		{"wc", "-w", NULL},
		{NULL}
	};

	((void)argc, (void)argv, (void)envp, (void)argvs); 
	init_shell(&mshell, envp);
	pipe_function(argvs, mshell.envlst, 0);
	clear_garbage(&mshell);
	return (0);
}
