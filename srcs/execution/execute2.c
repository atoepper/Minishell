/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/14 12:30:25 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function2(t_ast_node *node_command_term,
			t_ast_node *node_command, t_shell *mshell, int exit_status)
{
	while ((node_command != NULL))
	{
		if ((node_command->type & COMMAND))
		{
			if (node_command->argv == NULL)
				return (1);
			exit_status = exec_builtin(node_command_term,
					node_command->argv, mshell);
			if (exit_status)
			{
				exit_status = exec_external(node_command_term,
						node_command->argv, mshell);
				mshell->error = exit_status;
			}
			if (exit_status == 127 && ft_strncmp(node_command->argv[0],
					"./minishell", 12) != 0)
			{
				ft_putstr_fd("command not found: ", 2);
				ft_putstr_fd(node_command->argv[0], 2);
				ft_putstr_fd("\n", 2);
			}
		}
		node_command = node_command->next;
	}
	return (exit_status);
}

int	exec_function(t_ast_node *node_command_term, t_shell *mshell)
{
	int			exit_status;
	t_ast_node	*node_command;

	exit_status = 111;
	node_command = node_command_term->child;
	exit_status = exec_function2(node_command_term,
			node_command, mshell, exit_status);
	if (exit_status == 111)
	{
		node_command_term->out_fd[0] = node_command_term->in_fd[0];
		node_command_term->out_fd[1] = node_command_term->in_fd[1];
		mshell->error = 0;
		exit_status = 0;
	}
	return (exit_status);
}
