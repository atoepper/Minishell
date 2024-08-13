/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/08 14:46:47 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	init_shell(t_shell *mshell)
{
	ft_memset(mshell, 0, sizeof(t_shell));
	/* init environment */
	mshell->in = dup(0);
	mshell->out = dup(1);
	/* tcgetattr */
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv, (void)envp); 
	/* init data */
	init_shell(&mshell);
	while(1)
	{
		/* init signals */
		/* readline */
		mshell.line = readline("minishell> ");
		if (!mshell.line)
			return(free(mshell.line), 0);
		/* Testing */
		printf("%s\n", mshell.line);
		if (!ft_strncmp(mshell.line, "exit", 5))
			return(free(mshell.line), 0);
		/* update history */
		add_history(mshell.line);
		/* tokenize */
		/* parse */
		/* handle errors */
		/* execute parse tree */		
		free(mshell.line);
	}
	return (0);
}