/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/18 10:51:55 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	set_error_exe(t_shell *mshell, int errno)
{
	mshell->error = errno;
	return (errno);
}

void	ft_set_error(t_shell *mshell, int errno, enum e_err_type err_type)
{
	mshell->error = errno;
	mshell->err_type = err_type;
	ft_process_error(mshell);
}

void	ft_process_error(t_shell *mshell)
{
	enum e_err_type	err_type;

	err_type = mshell->err_type;
	if (err_type == MALLOC)
		ft_putstr_fd("minishell: malloc error\n", 2);
	else if (err_type == SYNTAX)
		ft_putstr_fd("minishell: syntax error near '|'\n", 2);
	else if (err_type == PARSE)
		ft_putstr_fd("minishell: parse error near unexpected token\n", 2);
	else if (err_type == OPEN_QUOTES)
		ft_putstr_fd("minishell: open quotes\n", 2);
	else if (err_type == NO_FILE)
		ft_putstr_fd("cd: no such directory or file\n", 2);
	else if (err_type == NO_FILE_RED)
		ft_putstr_fd("minishell: no such directory or file\n", 2);
	else if (err_type == EXIT_ARG)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else if (err_type == CD_ARG)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (err_type == EXIT_ARG_NUM)
		ft_putstr_fd("exit: numeric argument required\n", 2);
}

void	print2errorfile(char *str)
{
	int	fd_output;
	int	write_return;

	fd_output = open("errorfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	write_return = write(fd_output, str, ft_strlen(str));
	write_return = write(fd_output, "\n", 1);
	write_return++;
}
