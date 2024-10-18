/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:40:57 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/18 10:07:02 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	create_pipe(int *pipe_fd)
{
	if (pipe_fd[0] == 0)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}

int	add_re_out_to_pipe(t_ast_node *node_command_term, t_shell *mshell)
{
	t_ast_node	*node_command;

	node_command = node_command_term->child;
	while ((node_command != NULL && mshell->error == 0))
	{
		if ((node_command->type & WRITE))
			ouput_write(node_command_term, node_command->value, mshell);
		if ((node_command->type & WRITE_APPEND))
			ouput_write_append(node_command_term, node_command->value, mshell);
		node_command = node_command->next;
	}
	return (0);
}

int	add_re_in_to_pipe(t_ast_node *node_command_term, t_shell *mshell)
{
	t_ast_node	*node_command;

	node_command = node_command_term->child;
	while ((node_command != NULL && mshell->error == 0))
	{
		if ((node_command->type & READ))
			input_read(node_command_term, node_command->value, mshell);
		else if ((node_command->type & HEREDOC))
			input_heredoc(node_command_term, node_command->value, mshell);
		node_command = node_command->next;
	}
	return (0);
}

void	add_pipe_to_output(t_ast_node *node_command_term, t_shell *mshell)
{
	int	pipe_fd[2];

	if (node_command_term->next != NULL && node_command_term->fd[1] == 1)
	{
		if (pipe(pipe_fd) == -1)
			mshell->error = 1;
		node_command_term->fd[1] = pipe_fd[1];
		node_command_term->next->fd[0] = pipe_fd[0];
	}
}
