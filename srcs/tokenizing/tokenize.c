/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/06 10:26:50 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_tokenize(t_shell *mshell)
{
	if(ft_strlen(mshell->line) == 0) /* eigentlich : wenn line nur whitespaces hat*/
		return (0);
	mshell->token_list = ft_linetolist(mshell->line, &mshell->error);
	free(mshell->line);
	mshell->line = NULL;
	if (!mshell->token_list)
	{
		ft_set_error(mshell, 1, "Tokenizing failed\n");
		return (1);
	}
	expander(mshell);
	ft_joinwords(&mshell->token_list);
	return (0);
}