/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_by_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/03 13:17:27 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/minishell.h"

int	input_redirection(char *input)
{
	int	fd_input;

	fd_input = open(input, O_RDONLY);
	return (fd_input);
}
int	here_document(char *input)
{
	char	buf[1024];
	int		pipe_fd[2];

	ft_bzero(buf, 1024);
	input = ft_strjoin(input, "\n");
	if (input == NULL)
		return (perror("ft_strjoin"), 1);
	pipe(pipe_fd);
	while (ft_strncmp(buf, input, ft_strlen(input)) != 0)
	{
		ft_putstr_fd(buf, pipe_fd[1]);
		ft_bzero(buf, 1024);
		read(0, buf, 1024);
	}
	close(pipe_fd[1]);
	free(input);
	return(pipe_fd[0]);
}

int	ouput_redirection(int output_typ, char *output)
{
	int	fd_output;

	fd_output = -1;
	if (output_typ == 0)
		fd_output = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (output_typ == 1)
		fd_output = open(output, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd_output);
}

int	redirection_test(int input_typ, char *input, int output_typ, char *output)
{
	int		fd_input;
	int		fd_output;
	char	buf[1];
	int		count_read;

	fd_input = -1;
	fd_output = -1;
	ft_bzero(buf, ft_strlen(buf));
	if (input_typ == 0)
		fd_input = input_redirection(input);
	else if (input_typ == 1)
		fd_input = here_document(input);
	if (fd_input == -1)
		return(perror("fd_input"), 1);
	fd_output = ouput_redirection(output_typ, output);
	if (fd_output == -1)
		return(perror("fd_output"), 1);
	count_read = read(fd_input, buf, 1);
	while (count_read != 0)
	{
		ft_putstr_fd(buf, fd_output);
		count_read = read(fd_input, buf, 1);
	}
	close(fd_input);
	close(fd_output);
	return (0);
}

int	main(void)
{

	redirection_test(0, "../../testing/test.txt", 0, "../../testing/test1.txt");
	redirection_test(0, "../../testing/test.txt", 1, "../../testing/test2.txt");
	redirection_test(1, "EOF", 0, "../../testing/test3.txt");
	redirection_test(1, "EOF", 1, "../../testing/test4.txt");
	return (0);
}
