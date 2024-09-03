/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/03 16:17:33 by jweingar         ###   ########.fr       */
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
	//printf("tokenizing succeeded\n");
	expander(mshell);
	ft_joinwords(&mshell->token_list);
	return (0);
}