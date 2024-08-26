/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/26 15:30:46 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	exec_function(char **argv, char **env)
{
	if (argv == NULL)
		return (0);
	if (exec_builtin(argv, env))
		if (exec_external(argv, env))
			printf("command not found: %s\n", argv[0]);
	return (0);
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

int	pipe_function(char *argvs[2][6], int in_fd)
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
		exec_function(argvs[0]);
		exit(EXIT_SUCCESS);
	}
	else if (pid != 0)
	{
		wait(&exit_status);
		close(pipefd[1]);
		if (in_fd != 0)
			close(in_fd);
		pipe_function(argvs + 1, pipefd[0]);
	}
	return (0);
}