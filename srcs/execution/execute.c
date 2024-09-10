/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/10 16:45:03 by jweingar         ###   ########.fr       */
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
					printf("command not found: %s\n", node_command->argv[0]);
					exit_status = 1;
				}
			}
		}
		node_command = node_command->next;
	}
	return (exit_status);
}

int	execute_command_term(t_shell *mshell, t_ast_node *node_command_term, char *str)
{
	int			pipefd[2];
	int			pipefd2[2];
	pid_t		pid;
	int			exit_status;
	int			output;
	int			result;

	((void)mshell, (void)node_command_term);
	if (pipe(pipefd) == -1 || pipe(pipefd2) == -1)
		return (perror("pipe"), 1);
	result = 0;
	exit_status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
	{
		close(pipefd2[0]);
		add_redirection_to_pipe(node_command_term, str, pipefd[1]);
		if (str != NULL)
			dup2(pipefd[0], 0);
		close(pipefd[0]);
		dup2(pipefd2[1], 1);
		close(pipefd2[1]);
		exec_function(node_command_term, mshell);
		exit(exit_status);
	}
	else if (pid != 0)
	{
		wait(&exit_status);
		close(pipefd[0]);
		close(pipefd[1]);
		close(pipefd2[1]);
		str = read_fd_to_str(pipefd2[0]);
		output = add_str_to_redirections(node_command_term, str);
		if (node_command_term->next != NULL)
			execute_command_term(mshell, node_command_term->next, str);
		else if (output != 0)
			result = write(1, str, ft_strlen(str));
	}
	result++;
    return (0);
}

int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;

	node_command_term = mshell->ast->child;
	if (node_command_term != NULL)
		execute_command_term(mshell, node_command_term, NULL);
	return (0);
}
