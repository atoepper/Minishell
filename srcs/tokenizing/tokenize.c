/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/19 16:07:28 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_tokenize(t_shell *mshell)
{
	mshell->token_list = ft_linetolist(mshell->line, &mshell->error);
	free(mshell->line);
	mshell->line = NULL;
	if (!mshell->token_list)
	{
		printf("Tokenizing failed\n");
		/* Set error */
		return (1);
	}
	printf("tokenizing succeeded\n");
	ft_joinwords(&mshell->token_list);
	return (0);
}