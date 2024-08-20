/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:33:55 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/20 13:33:56 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(void)
{
	int		pipefd[2];
	pid_t	pid;
	char	*argv[] = {"echo", "n5", "hellorrrrr world", "bla", "blubb", NULL};
	char	*argv2[] = {"wc", NULL};
	int 	exit_status;
	//char	buf[1024];
	int		saved_std_out;
	int		saved_std_in;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);

	saved_std_out = dup(STDOUT_FILENO);
	saved_std_in = dup(STDIN_FILENO);

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);

	if (pid == 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exec_function(argv2);
		perror("execlp");
		exit(EXIT_FAILURE);
	} else {
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_function(argv);
		perror("execlp");
		exit(EXIT_FAILURE);
	}

	dup2(saved_std_out, STDOUT_FILENO);
	dup2(saved_std_in, STDIN_FILENO);
	close(saved_std_out);
	close(saved_std_in);

	wait(&exit_status);
	printf("status: %i\n", WEXITSTATUS(exit_status));

	return 0;
}
