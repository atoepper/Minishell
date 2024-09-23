/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:06:57 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:44:22 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_ast_node	*create_ast_node(int type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	node->type = type;
	if (value)
		node->value = strdup(value);
	else
		node->value = (NULL);
	node->argv = (NULL);
	node->child = (NULL);
	node->next = (NULL);
	return (node);
}

void	add_child_node(t_ast_node *parent, t_ast_node *child)
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

void	add_branch(t_ast_node *parent, t_ast_node *child)
{
	t_ast_node	*current;

	if (!parent->child)
		parent->child = child->child;
	else
	{
		current = parent->child;
		while (current->next)
			current = current->next;
		current->next = child->child;
	}
	free(child);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
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
// void	print_ast(t_ast_node *node, int indent)
// {
// 	if (!node)
// 		return ;
// 	for (int i = 0; i < indent; i++) printf("  ");

// 	if (node->type & PROGRAM)
// 		printf("Program\n");
// 	else if (node->type & COMMAND_TERM)
// 		printf("Command term\n");
// 	else if (node->type & COMMAND)
// 	{
// 		printf("Command: %s, ", node->argv[0]);
// 		for (int i = 0; node->argv[i]; i++) 
//			printf("argv[%d]: %s, ", i, node->argv[i]);
// 		printf("\n");
// 	}
// 	else if (node->type & REDIR_ITER)	
// 		printf("Redicection iteration\n");
// 	else if (node->type & REDIRECT)
// 	{
// 		printf("Redirecton:");
// 		if (node->type & READ)
// 			printf("type: read");
// 		else if (node->type & WRITE)
// 			printf("type: write");
// 		else if (node->type & WRITE_APPEND)
// 			printf("type: write/append");
// 		else if (node->type & HEREDOC)
// 			printf("type: heredoc");
// 		printf(", filepath/delimiter: %s\n", node->value);
// 	}
// 	if (node->child)
// 		print_ast(node->child, indent + 1);
// 	if (node->next)
// 		print_ast(node->next, indent);
// }
