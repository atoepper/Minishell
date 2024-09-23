/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:17:07 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:36:15 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_sig_term(int mode)
{
	set_signal(mode);
	set_termios(mode);
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

void	sigint_handler_newline(int signo)
{
	if (signo == SIGINT)
		write(2, "\n", 1);
}

void	set_signal(int mode)
{
	if (mode == NO_CHILD)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == WITH_CHILD)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == EXECUTE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == HEREDOC_PARENT)
	{
		signal(SIGINT, sigint_handler_newline);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	set_termios(int mode)
{
	struct termios	term_setting;

	tcgetattr(STDOUT_FILENO, &term_setting);
	if (mode == NO_CHILD || mode == WITH_CHILD
			|| mode == HEREDOC_PARENT || mode == HEREDOC_CHILD)
		term_setting.c_lflag &= ~(ECHOCTL);
	else if (mode == EXECUTE_CHILD)
		term_setting.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term_setting);
}
