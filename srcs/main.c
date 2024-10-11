/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:39 by atoepper         ###   ########.fr       */
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
			break ;
		add_history(mshell.line);
		ft_tokenize(&mshell);
		if (mshell.token_list != NULL)
			mshell.ast = parse_program(&mshell);
		execute_programm(&mshell);
		ft_process_error(&mshell);
		ft_renewshell(&mshell);
	}
	clear_garbage(&mshell);
	return (mshell.exit_prog_val);
}
