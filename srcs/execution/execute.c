/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/15 13:33:43 by jweingar         ###   ########.fr       */
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
	char		buf[2];

	buf[1] = '\0';
	exit_status = 111;
	node_command = node_command_term->child;
	exit_status = exec_function2(node_command_term,
			node_command, mshell, exit_status);
	if (exit_status == 111 && node_command_term->fd[0] != 0
		&& node_command_term->fd[1] != 1)
	{
		while (read(node_command_term->fd[0], buf, 1) != 0)
		{
			if (write(node_command_term->fd[1], buf, 1) != 1)
				return (perror("minishell"), 1);
		}
	}
	return (exit_status);
}

int	execute_command_term(t_shell *mshell, t_ast_node *node_command_term)
{
	add_re_in_to_pipe(node_command_term, mshell);
	add_re_out_to_pipe(node_command_term, mshell);
	if (mshell->error == 0)
		exec_function(node_command_term, mshell);
	if (node_command_term->next != NULL)
	{
		node_command_term->next->fd[0] = node_command_term->fd[0];
		execute_command_term(mshell, node_command_term->next);
	}
	return (0);
}

void	wait_for_all(t_ast_node	*node_command_term, t_shell *mshell)
{
	int	exit_status;

	while (node_command_term != NULL)
	{
		waitpid(node_command_term->pid, &exit_status, 0);
		node_command_term->exit_status = WEXITSTATUS(exit_status);
		mshell->error = node_command_term->exit_status;
		node_command_term = node_command_term->next;
	}
}

int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;

	if (mshell->ast == NULL)
		return (1);
	node_command_term = mshell->ast->child;
	if (node_command_term != NULL)
		execute_command_term(mshell, node_command_term);
	wait_for_all(node_command_term, mshell);
	return (0);
}
