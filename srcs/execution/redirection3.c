/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:37 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/08 15:41:57 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	add_str_to_redirections(t_ast_node *node_command_term, char *str, t_shell *mshell)
{
	t_ast_node	*node_command;
	int			output;

	node_command = node_command_term->child;
	output = 0;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE))
			output = ouput_write(node_command->value, str, mshell);
		if ((node_command->type & WRITE_APPEND))
			output = ouput_write_append(node_command->value, str, mshell);
		node_command = node_command->next;
	}
	return (output);
}

int	check_if_red_out(t_ast_node *node_command_term)
{
	t_ast_node	*node_command;
	int			output;

	node_command = node_command_term->child;
	output = 0;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE) || (node_command->type & WRITE_APPEND))
			output = 1;
		node_command = node_command->next;
	}
	return (output);
}
