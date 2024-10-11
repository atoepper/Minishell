/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:25:12 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/11 12:25:03 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token	*ft_newtoken(char *value, int type)
{
	t_token	*newtoken;

	newtoken = (t_token *)malloc(sizeof(t_token));
	if (!newtoken)
		return (NULL);
	newtoken->value = value;
	newtoken->type = type;
	newtoken->next = NULL;
	newtoken->prev = NULL;
	return (newtoken);
}

void	ft_addtoken(t_token **tokenlist, t_token *newtoken)
{
	t_token	*current;

	if (!*tokenlist)
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

void	ft_deltoken(t_token *token)
{
	free(token->value);
	free(token);
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

/* Tester */

// void	ft_printtypes(int type)
// {
// 	if (type & DQUOTE)
// 		printf("DQUOTE ");
// 	if (type & SQUOTE)
// 		printf("SQUOTE ");
// 	if (type & WORD)
// 		printf("WORD ");
// 	if (type & EXPANDER)
// 		printf("EXPANDER ");
// 	if (type & PIPE)
// 		printf("PIPE ");
// 	if (type & REDIRECT)
// 		printf("REDIRECT ");
// 	if (type & WRITE)
// 		printf("WRITE ");
// 	if (type & WRITE_APPEND)
// 		printf("WRITE APPEND ");
// 	if (type & HEREDOC)
// 		printf("HEREDOC ");
// 	if (type & READ)
// 		printf("READ ");
// 	if (type & RIGHT_JOIN)
// 		printf("RIGHT_JOIN");
// 	printf ("\n");
// }

// void	ft_printlist(t_token **tokenlist)
// {
// 	t_token	*current;

// 	current = *tokenlist;
// 	if (!tokenlist || !*tokenlist)
// 	{
// 		printf("list is empty\n");
// 		return ;
// 	}
// 	printf("token list: \n");
// 	while (current)
// 	{
// 		printf("Value: %s, Type: ", current->value);
// 		ft_printtypes(current->type);
// 		current = current->next;
// 	}
// }
