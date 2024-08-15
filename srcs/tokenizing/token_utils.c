/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:25:12 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/13 18:32:18 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token	*ft_newtoken(char *value, int type)
{
	t_token	*newtoken;

	newtoken = (t_token*)malloc(sizeof(t_token));
	if (!newtoken)
		return (NULL);
	newtoken->value = value;
	newtoken->type = type;
	newtoken->next = NULL;
	newtoken->prev = NULL;
	return(newtoken);
}

void	ft_addtoken(t_token **tokenlist, t_token *newtoken)
{
	t_token	*current;

	if (!tokenlist)
		*tokenlist = newtoken;
	else
	{
		current = *tokenlist;
		while (current && current->next)
			current = current->next;
		current->next = newtoken;
		newtoken->prev = current;
	}
}

void	ft_clear_tokenlist(t_token	**tokenlist)
{
	t_token	*current;
	t_token	*tmp;

	current = *tokenlist;
	if (!current)
		return ;
	while (current)
	{
		free(current->value);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*tokenlist = NULL;
}

void	ft_printlist(t_token **tokenlist)
{
	t_token	*current;

	current = *tokenlist;
	while (current)
	{
		printf("Value: %s, Type; %i\n", current->value, current->type);
		current = current->next;
	}
	
}
