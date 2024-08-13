/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:57:51 by atoepper          #+#    #+#             */
/*   Updated: 2024/07/02 17:08:36 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_cd(const char *path)
{
	if (!path)
		/* go home */
	if (chdir(path) != EXIT_SUCCESS)
		/* error msg, return 1 */	
	/* update envp */
	return(0);
}
