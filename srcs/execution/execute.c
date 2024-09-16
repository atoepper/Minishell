/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/16 12:38:18 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(t_ast_node *node_command_term, t_shell *mshell)
{
	int			exit_status;
	t_ast_node	*node_command;

	exit_status = 1;
	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & COMMAND))
		{
			if (node_command->argv == NULL)
				return (0);
			exit_status = exec_builtin(node_command->argv, mshell);
			if (exit_status)
			{
				exit_status = exec_external(node_command->argv, mshell);
				if (exit_status)
				{
					ft_putstr_fd("command not found\n", 1);
					exit_status = 127;
				}
			}
		}
		node_command = node_command->next;
	}
	return (exit_status);
}

int	exe_child(int *pipefd_input, int *pipefd_output,
			t_ast_node *node_command_term, t_shell *mshell)
{
	int	exit_status;

	close(pipefd_input[1]);
	close(pipefd_output[0]);
	dup2(pipefd_input[0], 0);
	close(pipefd_input[0]);
	dup2(pipefd_output[1], 1);
	close(pipefd_output[1]);
	exit_status = exec_function(node_command_term, mshell);
	return (exit_status);
}


int	execute_command_term(t_shell *mshell,
			t_ast_node *node_command_term, char *str)
{
	int			pipefd_input[2];
	int			pipefd_output[2];
	pid_t		pid;
	int			exit_status;
	int			output;


	if (pipe(pipefd_input) == -1 || pipe(pipefd_output) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		exit_status = exe_child(pipefd_input, pipefd_output,
				node_command_term, mshell);
		exit(exit_status);
	}
	else if (pid != 0)
	{
		close(pipefd_input[0]);
		close(pipefd_output[1]);
		add_redirection_to_pipe(node_command_term, str, pipefd_input[1]);
		close(pipefd_input[1]);
		wait(&exit_status);
		str = read_fd_to_str(pipefd_output[0]);
		output = add_str_to_redirections(node_command_term, str);
		if (node_command_term->next != NULL)
			exit_status = execute_command_term(mshell, node_command_term->next, str);
		else if (output != 0)
			ft_putstr_fd(str, 1);
	}
    return (exit_status);
}

int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;

	node_command_term = mshell->ast->child;
	if (node_command_term != NULL)
		mshell->exit_status = execute_command_term(mshell, 
				node_command_term, NULL);
	return (0);
}
