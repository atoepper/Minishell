/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/03 12:03:09 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	redirection_test(char *delimiter, char *output, int out_typ)
{
	int		fd_output;
	char	buf[1024];
	int		count_read;
	int		pipe_fd[2];
	//int		count_write;

	((void)delimiter, (void)out_typ);
	delimiter = ft_strjoin(delimiter, "\n");
	if (delimiter == NULL)
		return (perror("ft_strjoin"), 1);
	pipe(pipe_fd);
	count_read = 0;
	ft_bzero(buf, 1024);
	if (out_typ == 0)
		fd_output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (out_typ == 1)
		fd_output = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return(free(delimiter), printf("wrong out_typ\n"), 1);	
	count_read = read(0, buf, 1024);
	while (ft_strncmp(buf, delimiter, ft_strlen(delimiter)) != 0)
	{
		ft_putstr_fd(buf, pipe_fd[1]);
		ft_bzero(buf, 1024);
		count_read = read(0, buf, 1024);
	}
	close(pipe_fd[1]);
	ft_bzero(buf, 1024);
	read(pipe_fd[0], buf, 1024);
	close(pipe_fd[0]);
	ft_putstr_fd(buf, fd_output);
	close(fd_output);
	free(delimiter);
	return (0);
}

int	main(void)
{
	char	delimiter[] = "EOF";
	char	output1[] = "../../testing/test1.txt";

	redirection_test(delimiter, output1, 0);
	return (0);	
}
