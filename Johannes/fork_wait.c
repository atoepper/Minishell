/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:06:46 by jweingar          #+#    #+#             */
/*   Updated: 2024/08/15 16:24:11 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	main(void)
{
	pid_t pid;
	int exit_status;
	const char *pathname = "/bin/echo";
    char *argv[] = {"echo", "-n", "Hello wwwworld!" "test1", NULL};

    char *envp[] = {NULL};
	
	pid = fork();

	if (pid < 0)
	{
        perror("fork");
        exit(EXIT_FAILURE);
    }
	
    if (pid == 0)
	{
        if (execve(pathname, argv, envp) == -1)
		{
            perror("execve");
            exit(EXIT_FAILURE);
        }
	}
	else
        wait(&exit_status);
	ft_echo(argv);
	


	return (0);
}