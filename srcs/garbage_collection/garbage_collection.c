/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:57:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/23 11:42:47 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	clear_garbage(t_shell *mshell)
{
	free(mshell->line);
	mshell->line = NULL;
	free(mshell->prompt);
	mshell->prompt = NULL;
	ft_clear_tokenlist(&mshell->token_list);
	mshell->token_list = NULL;
	ft_clear_envlist(&mshell->envlst);
	mshell->envlst = NULL;
	free_lst_builtin(mshell->lst_builtins);
	mshell->lst_builtins = NULL;
	return (0);
}
