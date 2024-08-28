/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 16:19:53 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv, (void)envp); 
	/* init data */
	init_shell(&mshell, envp);
	// ft_printenvlist(&mshell);
	while(1)
	{
		/* init signals */
		/* readline */
		mshell.line = readline(mshell.prompt);
		if (!mshell.line)
			return(free(mshell.line), 0);
		/* Testing */
		printf("%s\n", mshell.line);
		if (!ft_strncmp(mshell.line, "exit", 5))
			return(free(mshell.line), 0);
		/* update history */
		add_history(mshell.line);
		/* tokenize */
		ft_tokenize(&mshell);
		ft_printlist(&mshell.token_list);
		/* parse */
		/* handle errors */
		/* execute parse tree */		
		create_prompt(&mshell);
		ft_clear_tokenlist(&mshell.token_list);
		free(mshell.line);
	}
	ft_clear_envlist(&mshell.envlst);
	return (0);
}
