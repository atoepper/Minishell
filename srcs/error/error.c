/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 10:07:27 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_set_error(t_shell *mshell, int errno, char *msg)
{
	mshell->error = errno;
	ft_putstr_fd(msg, 2);
}

void	print2errorfile(char *str)
{
	int	fd_output;
	int	write_return;

	fd_output = open("errorfile.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	write_return = write(fd_output, str, ft_strlen(str));
	write_return++;
}
