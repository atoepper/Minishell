/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/11 13:26:52 by atoepper         ###   ########.fr       */
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
}

void	ft_process_error(t_shell *mshell)
{
	enum e_err_type	err_type;

	err_type = mshell->err_type;
	if (mshell->error == 0 || err_type == NO_ERR)
		return ;
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
		ft_putstr_fd("exit: too many arguments", 2);
	else if (err_type == PWD_ARG)
		ft_putstr_fd("pwd: too many arguments", 2);
}

void	print2errorfile(char *str)
{
	int	fd_output;
	int	write_return;

	fd_output = open("errorfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	write_return = write(fd_output, str, ft_strlen(str));
	write_return++;
}
