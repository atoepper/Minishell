/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/16 13:54:29 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(t_ast_node *node_command_term, t_shell *mshell)
{
	int			exit_status;
	t_ast_node	*node_command;

	exit_status = 111;
	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & COMMAND))
		{
			if (node_command->argv == NULL)
				return (1);
			exit_status = exec_builtin(node_command->argv, mshell);
			if (exit_status)
				exit_status = exec_external(node_command->argv, mshell);
			mshell->exit_status = exit_status;
		}
		node_command = node_command->next;
	}
	return (exit_status);
}

int	exe_child(int *pipefd_input, int *pipefd_output,
			t_ast_node *node_command_term, t_shell *mshell)
{
	int		exit_status;
	char	buf[2];

	buf[1] = '\0';
	close(pipefd_input[1]);
	close(pipefd_output[0]);
	dup2(pipefd_input[0], 0);
	close(pipefd_input[0]);
	dup2(pipefd_output[1], 1);
	close(pipefd_output[1]);
	exit_status = exec_function(node_command_term, mshell);
	if (exit_status == 111)
		while (read(0, buf, 1))
			ft_putstr_fd(buf, 1);
	return (exit_status);
}


int	execute_command_term(t_shell *mshell,
			t_ast_node *node_command_term, char *str)
{
	int			pipefd_in[2];
	int			pipefd_out[2];
	pid_t		pid;
	int			output;
	int			exit_status;

	if (pipe(pipefd_in) == -1 || pipe(pipefd_out) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), EXIT_FAILURE);
	if (pid == 0)
		exit(exe_child(pipefd_in, pipefd_out, node_command_term, mshell));
	else if (pid != 0)
	{
		add_redirection_to_pipe(node_command_term, str, pipefd_in, pipefd_out);
		wait(&exit_status);
		str = read_fd_to_str(pipefd_out[0]);
		output = add_str_to_redirections(node_command_term, str);
		if (node_command_term->next != NULL)
			execute_command_term(mshell, node_command_term->next, str);
		else if (output != 0)
			ft_putstr_fd(str, 1);
	}
    return (0);
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
