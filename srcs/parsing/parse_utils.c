/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:06:56 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/10 12:41:09 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_count_args(t_ast_node **command)
{
	t_ast_node	*node;
	int			argc;

	node = *command;
	argc = 0;
	while (node != NULL)
	{
		argc++;
		node = node->next;
	}
	return (argc);
}

int	ft_create_argv(t_ast_node *command)
{
	int			argc;
	int			i;
	char		**argv;
	t_ast_node	*node;

	argc = ft_count_args(&command->child);
	i = 0;
	node = command->child;
	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (1); /* malloc error */
	while (i < argc)
	{
		argv[i] = ft_strdup(node->value);
		node = node->next;
		i++;
	}
	argv[i] = NULL;
	command->argv = argv;
	if (command->child != NULL)
		free_ast(command->child);
	command->child = NULL;
	return (0);
}

// char	**ft_create_argv(t_token **current, int argc)
// {
// 	char	**argv;
// 	t_token	*token_ptr;
// 	int		i;

// 	i = 0;
// 	token_ptr = *current;
// 	argv = (char **)malloc(sizeof(char *) * (argc + 1));
// 	if (!argv)
// 		return (NULL);
// 	while (i < argc)
// 	{
// 		argv[i] = ft_strdup(token_ptr->value);
// 		token_ptr = token_ptr->next;
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }
