/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_in_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:13:29 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/19 11:18:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

char	*read_fd_to_str(int fd)
{
	char	buffer[1];
	char	*str;
	char	*new_str;
	int		rt_read;

	rt_read = read(fd, buffer, 1);
	while (rt_read == 1)
	{
		new_str = ft_strjoin(str, buffer);
		if (new_str == NULL)
			return (free(str), NULL);
		free (str);
		str = new_str;
		rt_read = read(fd, buffer, 1);
	}
	new_str = ft_strjoin(str, "\0");
	if (new_str == NULL)
		return (free(str), NULL);
	free (str);
	str = new_str;
	return (str);
}

int	main(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	*argv[] = {"/bin/pwd", NULL};
    char	*envp[] = {NULL};
	char	*str;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve("/bin/pwd", argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		str = read_fd_to_str(pipefd[0]);
		if (str == NULL)
		{
			perror("malloc");
			return (1);
		}
		printf("%s", str);
		free(str);
	}
}
