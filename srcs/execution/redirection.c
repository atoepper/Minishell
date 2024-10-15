/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/15 13:33:09 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	input_read(t_ast_node *node_command_term, char *input, t_shell *mshell)
{
	int	fd;

	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		mshell->error = 1;
		return (perror("minishell"), 1);
	}
	else
	{
		if (node_command_term->fd[0] != 0)
			close(node_command_term->fd[0]);
		node_command_term->fd[0] = fd;
	}
	return (0);
}

int	input_heredoc(t_ast_node *node_command_term, char *input, t_shell *mshell)
{
	char	buf[1024];
	int		read_return;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	node_command_term->fd[0] = pipe_fd[0];
	ft_bzero(buf, 1024);
	input = ft_strjoin(input, "\n");
	if (input == NULL)
		return (ft_set_error(mshell, 1, MALLOC), 1);
	read_return = read(0, buf, 1024);
	buf[read_return] = '\0';
	set_sig_term(IN_HEREDOC);
	while (ft_strncmp(buf, input, ft_strlen(input)) != 0)
	{
		ft_putstr_fd(buf, pipe_fd[1]);
		ft_bzero(buf, 1024);
		read_return = read(0, buf, 1024);
		buf[read_return] = '\0';
	}
	free(input);
	close(pipe_fd[1]);
	set_sig_term(NO_CHILD);
	return (0);
}

int	ouput_write(t_ast_node *node_command_term, char *path, t_shell *mshell)
{
	int	fd_output;

	fd_output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		mshell->error = 1;
		return (perror("minishell"), 1);
	}
	else
	{
		if (node_command_term->fd[1] != 1)
			close(node_command_term->fd[1]);
		node_command_term->fd[1] = fd_output;
	}
	return (0);
}

int	ouput_write_append(t_ast_node *node_command_term, char *path,
	t_shell *mshell)
{
	int	fd_output;

	fd_output = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_output == -1)
	{
		mshell->error = 1;
		return (perror("minishell"), 1);
	}
	else
	{
		if (node_command_term->fd[1] != 1)
			close(node_command_term->fd[1]);
		node_command_term->fd[1] = fd_output;
	}
	return (0);
}
