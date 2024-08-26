/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_Johannes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/26 11:28:50 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

// int	pipe_function(char *argvs[2][6], int in_fd)
// {
// 	int		pipefd[2];
// 	pid_t	pid;
// 	int		exit_status;

// 	if (argvs[0][0] == NULL)
// 		return (0);
// 	if (pipe(pipefd) == -1)
// 		return (perror("pipe"), 1);
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		return (EXIT_FAILURE);
// 	}
// 	if (pid == 0)
// 	{
// 		if (in_fd != 0)
// 		{
// 			dup2(in_fd, 0);
// 			close(in_fd);
// 		}
// 		if (argvs[1][0] != NULL)
// 			dup2(pipefd[1], 1);
// 		close(pipefd[0]);
// 		exec_function(argvs[0]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else if (pid != 0)
// 	{
// 		wait(&exit_status);
// 		close(pipefd[1]);
// 		if (in_fd != 0)
// 			close(in_fd);
// 		pipe_function(argvs + 1, pipefd[0]);
// 	}
// 	return (0);
// }

int	main(void)
{
	char *argvs[][6] = {
		{"cd", "/home/jweingar/Documents/projects/minishell/exercises/Johannes/objs/", NULL},
		{"pwd", NULL},
		{NULL}
	};

	(void)argvs;
	chdir("/home/jweingar/Documents/projects/minishell/exercises/Johannes/objs/");
	ft_pwd(argvs[1]);
//	ft_cd(argvs[0]);
//	pipe_function(argvs, 0);
}
