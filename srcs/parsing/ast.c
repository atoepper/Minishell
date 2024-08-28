/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:06:57 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/28 11:28:32 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_ast_node *create_ast_node(int type, char *value)
{
    t_ast_node *node = malloc(sizeof(t_ast_node));
    node->type = type;
	if (value)
    	node->value = strdup(value);
	else
		node->value = NULL;
	node->argv = NULL;
    node->child = NULL;
    node->next = NULL;
    return node;
}

void add_child_node(t_ast_node *parent, t_ast_node *child)
{
	t_ast_node	*current;
	if (!parent->child)
		parent->child = child;
	else
	{
		current = parent->child;
		while (current->next)
			current = current->next;
		current->next = child;
	}
}

void free_ast(t_ast_node *node)
{
	if (!node) return;
	if (node->child)
		free_ast(node->child);
	if (node->next)
		free_ast(node->next);
	if (node->value)
		free(node->value);
	if (node->argv)
		free_array(node->argv);
	free(node);
}

/* ONLY FOR DEBUG */
// void print_ast(t_ast_node *node, int indent)
// {
// 	if (!node) return;
// 	for (int i = 0; i < indent; i++) printf("  ");

// 	switch (node->type)
// 	{
// 		case PROGRAM: printf("Program\n"); break;
// 		case PIPE: printf("Pipeline\n"); break;
// 		case COMMAND_TERM: printf("Command term\n"); break;
// 		case COMMAND: printf("Command\n"); break;
// 		case REDIR_ITER: printf("Redirection Iteration\n"); break;
// 		case REDIR_TERM: printf("Redirection term\n"); break;
// 		case REDIRECT: printf("Redirection\n"); break;
// 	}
// 	if (node->child)
// 		print_ast(node->child, indent + 1);
// 	if (node->next)
// 		print_ast(node->next, indent);
// }
