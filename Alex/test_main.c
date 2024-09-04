/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:19:56 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/04 10:33:43 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

void	ft_renewshell(t_shell *mshell)
{
		create_prompt(mshell);
		ft_clear_tokenlist(&(mshell->token_list));
		free_ast(mshell->ast);
		mshell->exit_status = mshell->error;
		mshell->error = 0;
		free(mshell->line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv, (void)envp); 
	init_shell(&mshell, envp);
	while(1)
	{
		/* init signals */
		mshell.line = readline(mshell.prompt);
		if (!mshell.line)
			return(free(mshell.line), 0);
		add_history(mshell.line);
		ft_tokenize(&mshell);
		mshell.ast = parse_program(&mshell);
		print_ast(mshell.ast, 0);
		/* execute parse tree */
		ft_renewshell(&mshell);
	}
	ft_clear_envlist(&mshell.envlst);
	return (0);
}
