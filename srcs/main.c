/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:22:17 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/15 13:42:18 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"
#include <readline/readline.h>

int	g_signal_flag = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	mshell;

	((void)argc, (void)argv);
	init_shell(&mshell, envp);
	while (!mshell.is_exit_prog)
	{
		mshell.line = readline(mshell.prompt);
		if (g_signal_flag == 1)
			mshell.exit_prog_val = 130;
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
	ft_putstr_fd("exit\n", 1);
	return (mshell.exit_prog_val);
}
