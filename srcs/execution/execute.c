/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 15:29:40 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(t_ast_node *node_command_term, t_shell *mshell, int *pipefd_in, int *pipefd_out)
{
	int			exit_status;
	t_ast_node	*node_command;
	char		buf[2];

	buf[1] = '\0';
	exit_status = 111;
	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & COMMAND))
		{
			if (node_command->argv == NULL)
				return (1);
			exit_status = exec_builtin(node_command->argv, mshell, pipefd_out[1]);
			if (exit_status)
				exit_status = exec_external(node_command->argv, mshell, pipefd_in, pipefd_out);
			if (exit_status == 127)
			{
				ft_putstr_fd("command not found: ", 2);
				ft_putstr_fd(node_command->argv[0], 2);
				ft_putstr_fd("\n", 2);
			}
			mshell->error = exit_status;
		}
		node_command = node_command->next;
	}
	//printf("%i, %i, %i, %i\n", pipefd_in[0], pipefd_in[1], pipefd_out[0], pipefd_out[1]);
	close(pipefd_in[1]);
	if (exit_status == 111)
		while (read(pipefd_in[0], buf, 1))
			ft_putstr_fd(buf, pipefd_out[1]);
	close(pipefd_in[0]);
	return (exit_status);
}

int	execute_command_term(t_shell *mshell,
			t_ast_node *node_command_term, char *str)
{
	int			pipefd_in[2];
	int			pipefd_out[2];
	int			output;

	if (pipe(pipefd_in) == -1 || pipe(pipefd_out) == -1)
		return (perror("pipe"), 1);
	add_redirection_to_pipe(node_command_term, str, pipefd_in[1]);
	exec_function(node_command_term, mshell, pipefd_in, pipefd_out);
	close(pipefd_out[1]);
	str = read_fd_to_str(pipefd_out[0]);
	output = add_str_to_redirections(node_command_term, str);
	if (node_command_term->next != NULL)
		execute_command_term(mshell, node_command_term->next, str);
	else if (output != 0)
	{
		mshell->last_output = str;
		ft_putstr_fd(str, 1);
	}
    return (0);
}

int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;
	if (mshell->ast == NULL)
		return (1);
	node_command_term = mshell->ast->child;
	if (node_command_term != NULL)
		execute_command_term(mshell, node_command_term, NULL);
	return (0);
}
