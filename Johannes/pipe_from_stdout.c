/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_from_stdout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:54:07 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/20 12:54:30 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(void)
{
	int		pipefd[2];
	int 	exit_status;
	char	buf[1024];
	int		saved_std_out;

	exit_status = 0;
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (1);
	}
	saved_std_out = dup(STDOUT_FILENO);
	write(1, "test1", 5);
	dup2(pipefd[1], 1);
	write(1, "hello", 5);
	read(pipefd[0], buf, 5);
	buf[5] = '\0';
	dup2(saved_std_out, 1);
	printf(" tesst2: %s\n", buf);
	return (0);
}
