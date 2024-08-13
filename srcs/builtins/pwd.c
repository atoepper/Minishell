/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:51:47 by atoepper          #+#    #+#             */
/*   Updated: 2024/07/02 16:54:41 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
