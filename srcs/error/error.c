/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:53:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/04 10:20:58 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_set_error(t_shell *mshell, int errno, char *msg)
{
	mshell->error = errno;
	ft_putstr_fd(msg, 2);
}
