/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:40:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;
	((void)argc, (void)argv);
	init_shell(&mshell, envp);
	while (!mshell.is_exit_prog)
	{
		mshell.line = readline(mshell.prompt);
		if (!mshell.line)
			return (free(mshell.line), 0);
		add_history(mshell.line);
		ft_tokenize(&mshell);
		mshell.ast = parse_program(&mshell);
		execute_programm(&mshell);
		if (is_output_without_nl(&mshell))
			printf("%%\n");
		ft_renewshell(&mshell);
	}
	clear_garbage(&mshell);
	return (mshell.exit_prog_val);
}
