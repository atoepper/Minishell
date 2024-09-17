/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 15:21:40 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv, (void)envp); 
	init_shell(&mshell, envp);
	while(!mshell.is_exit_prog)
	{
		/* init signals */
		mshell.line = readline(mshell.prompt);
		if (!mshell.line)
			return(free(mshell.line), 0);
		add_history(mshell.line);
		ft_tokenize(&mshell);
		mshell.ast = parse_program(&mshell);
		//print_ast(mshell.ast, 0);
		execute_programm(&mshell);
		// if (is_output_without_nl(&mshell))
		// 	printf("%%\n");
		ft_renewshell(&mshell);
	}
	clear_garbage(&mshell);
	return (mshell.exit_prog_val);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	t_shell	mshell;
// 	((void)argc, (void)argv, (void)envp); 
// 	/* init data */
// 	init_shell(&mshell, envp);
// 	// ft_printenvlist(&mshell);
// 	while(1)
// 	{
// 		/* init signals */
// 		/* readline */
// 		mshell.line = readline(mshell.prompt);
// 		if (!mshell.line)
// 			return(free(mshell.line), 0);
// 		/* Testing */
// 		//printf("%s\n", mshell.line);
// 		if (!ft_strncmp(mshell.line, "exit", 5))
// 			return(free(mshell.line), 0);
// 		/* update history */
// 		add_history(mshell.line);
// 		/* tokenize */
// 		ft_tokenize(&mshell);
// 		ft_printlist(&mshell.token_list);
// 		/* parse */
// 		mshell.ast = parse_program(&mshell);
		
// 		print_ast(mshell.ast, 0);
// 		/* handle errors */
// 		/* execute parse tree */
// 		// execute_programm(&mshell);	
// 		create_prompt(&mshell);
// 		ft_clear_tokenlist(&mshell.token_list);
// 		free(mshell.line);
// 	}
// 	ft_clear_envlist(&mshell.envlst);
// 	return (0);
// }
