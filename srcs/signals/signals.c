/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:17:07 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 10:58:47 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	sigtermset(int mode)
{
	set_signal(mode);
	// set_termios(mode);
}

void	sigint_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	sigint_handler_print_newline(int signo)
{
	if (signo == SIGINT)
		write(2, "\n", 1);
}

void	set_signal(int mode)
{
	(void)mode;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}


// static void	ft_sigint_handler(int num)
// {
// 	(void)num;
// 	if (g_minishell.signint_child)
// 	{
// 		ft_putstr_fd("\n", 1);
// 		g_minishell.signint_child = false;
// 		g_minishell.heredoc_sigint = true;
// 	}
// 	else
// 	{
// 		ft_putstr_fd("\n", 1);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// void	ft_sigquit_handler(int num)
// {
// 	(void)num;
// 	ft_putstr_fd("Quit: 3\n", 1);
// }

// void	ft_init_signals(void)
// {
// 	struct termios	term;

// 	term = g_minishell.original_term;
// 	term.c_lflag &= ~ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	g_minishell.heredoc_sigint = false;
// 	g_minishell.signint_child = false;
// 	signal(SIGINT, ft_sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }
