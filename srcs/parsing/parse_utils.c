/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:06:56 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/03 12:07:09 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_count_args(t_token **current)
{
	t_token	*token_ptr;
	int	argc;

	token_ptr = *current;
	argc = 0;
	while (token_ptr && token_ptr->type & WORD)
	{
		argc++;
		token_ptr = token_ptr->next;
	}
	return (argc);
} 

char	**ft_create_argv(t_token **current, int argc)
{
	char	**argv;
	t_token	*token_ptr;
	int		i;

	i = 0;
	token_ptr = *current;
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	while (i < argc)
	{
		argv[i] = ft_strdup(token_ptr->value);
		token_ptr = token_ptr->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}