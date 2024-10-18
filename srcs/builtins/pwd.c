/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:51:47 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/16 12:11:36 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_pwd(char **argv, t_shell *mshell, int fd)
{
	char	*pwd;
	int		return_val;

	((void)argv, (void)mshell);
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	return_val = write(fd, pwd, ft_strlen(pwd));
	return_val = write(fd, "\n", 1);
	free(pwd);
	return_val++;
	return (0);
}
