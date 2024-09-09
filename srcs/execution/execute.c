/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/09 10:27:42 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(char **argv, t_shell *mshell)
{
	int	exit_status;

	if (argv == NULL)
		return (0);
	exit_status = exec_builtin(argv, mshell);
	if (exit_status)
	{
		exit_status = exec_external(argv, mshell);
		if (exit_status)
			printf("command not found: %s\n", argv[0]);
	}
	return (exit_status);
}

char	*read_fd_to_str(int fd)
{
	char	buffer[1024];
	char	*str;
	int		rt_read;

	rt_read = read(fd, buffer, 1024);
	if (rt_read < 0)
		return (perror("read"), NULL);
	else
	{
		str = ft_strdup(buffer);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

int	pipe_function(char *argvs[][6], t_shell *mshell, int in_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_status;

	if (argvs[0][0] == NULL)
		return (0);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (in_fd != 0)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (argvs[1][0] != NULL)
			dup2(pipefd[1], 1);
		close(pipefd[0]);
		exec_function(argvs[0], mshell);
		exit(EXIT_SUCCESS);
	}
	else if (pid != 0)
	{
		wait(&exit_status);
		close(pipefd[1]);
		if (in_fd != 0)
			close(in_fd);
		pipe_function(argvs + 1, mshell, pipefd[0]);
	}
	return (0);
}

int	execute_command(t_shell *mshell, t_ast_node *node_command)
{
	while (!(node_command->type & COMMAND))
	{
		node_command = node_command->next;
	}
	exec_function(node_command->argv, mshell);
	return (0);
}

int	execute_command_term(t_shell *mshell, t_ast_node *node_command_term, int in_fd)
{
	int		pipefd[2];
	pid_t	pid;
	int		exit_status;

	if (node_command_term == NULL)
		return (0);
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (in_fd != 0)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if (node_command_term->next != NULL)
			dup2(pipefd[1], 1);
		close(pipefd[0]);
		execute_command(mshell, node_command_term->child);
		exit(EXIT_SUCCESS);
	}
	else if (pid != 0)
	{
		wait(&exit_status);
		close(pipefd[1]);
		if (in_fd != 0)
			close(in_fd);
		execute_command_term(mshell, node_command_term->next, pipefd[0]);
	}
	return (exit_status);
}

int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;

	node_command_term = mshell->ast->child;
	execute_command_term(mshell, node_command_term, 0);
	return (0);
}
