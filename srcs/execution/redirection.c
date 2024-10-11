/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/11 15:36:47 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	input_read(char *input, int fd_input, t_shell *mshell)
{
	int		fd;
	char	buf[2];

	(void)mshell;
	buf[1] = '\0';
	fd = open(input, O_RDONLY);
	if (fd == -1)
		return (perror("minishell"), 1);
	while (read(fd, buf, 1) == 1)
		ft_putstr_fd(buf, fd_input);
	close(fd);
	return (0);
}

int	input_heredoc(char *input, int fd_input, t_shell *mshell)
{
	char	buf[1024];
	int		read_return;

	ft_bzero(buf, 1024);
	input = ft_strjoin(input, "\n");
	if (input == NULL)
		return (ft_set_error(mshell, 1, MALLOC), 1);
	read_return = read(0, buf, 1024);
	buf[read_return] = '\0';
	set_sig_term(IN_HEREDOC);
	while (ft_strncmp(buf, input, ft_strlen(input)) != 0)
	{
		ft_putstr_fd(buf, fd_input);
		ft_bzero(buf, 1024);
		read_return = read(0, buf, 1024);
		buf[read_return] = '\0';
	}
	set_sig_term(NO_CHILD);
	return (0);
}

int	check_redirection_output(t_ast_node *node_command_term, t_shell *mshell)
{
	t_ast_node	*node_command;

	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE || node_command->type & WRITE_APPEND))
		{
			if (access(node_command->value, F_OK)
				&& !access(node_command->value, W_OK))
			{
				mshell->error = 1;
				perror("minishell");
				return (1);
			}
		}
		node_command = node_command->next;
	}
	return (0);
}

bool	ouput_write(char *path, char *str, t_shell *mshell)
{
	int	fd_output;
	int	write_return;

	fd_output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_output == -1)
	{
		perror("minishell");
		mshell->error = 1;
	}
	write_return = write(fd_output, str, ft_strlen(str));
	if (write_return != -1)
		return (1);
	close(fd_output);
	return (0);
}

bool	ouput_write_append(char *path, char *str, t_shell *mshell)
{
	int	fd_output;

	fd_output = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_output == -1)
	{
		perror("minishell");
		mshell->error = 1;
	}
	if (write(fd_output, str, ft_strlen(str)) != -1)
		return (1);
	close(fd_output);
	return (0);
}
