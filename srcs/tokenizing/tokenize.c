/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:14 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/11 12:21:19 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_joinwords(t_token **list)
{
	t_token	*current;
	t_token	*tmp;
	char	*joint;

	current = *list;
	while (current->next != NULL)
	{
		if (current->type & RIGHT_JOIN)
		{
			joint = ft_strjoin(current->value, current->next->value);
			if (!joint)
				return (1);
			free(current->value);
			current->value = joint;
			if (!(current->next->type & RIGHT_JOIN))
				current->type &= ~RIGHT_JOIN;
			tmp = current->next;
			current->next = current->next->next;
			ft_deltoken(tmp);
		}
		else
			current = current->next;
	}
	return (0);
}

int	ft_tokenize(t_shell *mshell)
{
	if (ft_string_is_empty(mshell->line))
		return (0);
	mshell->token_list = ft_linetolist(mshell, mshell->line, &mshell->error);
	if (mshell->error != 0)
		return (1);
	if (mshell->token_list)
	{
		expander(mshell);
		ft_joinwords(&mshell->token_list);
	}
	free(mshell->line);
	mshell->line = NULL;
	return (0);
}
