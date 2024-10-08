/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/08 10:43:04 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	input_read(char *input, int fd_input, t_shell *mshell)
{
	int		fd;
	char	buf[2];

	buf[1] = '\0';
	fd = open(input, O_RDONLY);
	if (fd == -1)
		return(ft_set_error(mshell, 1,
				"minishell: No such file or directory\n"), 1);
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
		return (ft_set_error(mshell, 1, "minishell: ft_strjoin heredoc\n"), 1);
	read_return = read(0, buf, 1024);
	buf[read_return] = '\0';
	while (ft_strncmp(buf, input, ft_strlen(input)) != 0)
	{
		ft_putstr_fd(buf, fd_input);
		ft_bzero(buf, 1024);
		read_return = read(0, buf, 1024);
		buf[read_return] = '\0';
	}
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
			if (access(node_command->value, F_OK))
				if (!access(node_command->value, W_OK))
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
	return (0);
}

char	*read_fd_to_str(t_ast_node *node_command_term)
{
	char	buf[2];
	char	*str;
	char	*new_str;

	close(node_command_term->out_fd[1]);
	buf[1] = '\0';
	str = NULL;
	while (read(node_command_term->out_fd[0], buf, 1) == 1)
	{
		new_str = ft_strjoin(str, buf);
		if (new_str == NULL)
			return (free(str), NULL);
		free(str);
		str = new_str;
	}
	close(node_command_term->out_fd[0]);
	return (str);
}

int	write_str_to_fd(char *str, int fd)
{
	int		result;

	if (str == NULL)
		return (-1);
	result = write(fd, str, ft_strlen(str));
	close(fd);
	result++;
	return (0);
}

int create_pipe(t_ast_node *node_command_term)
{
	if (node_command_term->in_fd[0] == 0)
	{
		if (pipe(node_command_term->in_fd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}

int	add_redirection_to_pipe(t_ast_node *node_command_term, t_shell *mshell)
{
	t_ast_node	*node_command;

	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & READ))
		{
			create_pipe(node_command_term);
			input_read(node_command->value,
					node_command_term->in_fd[1], mshell);
		}
		else if ((node_command->type & HEREDOC))
		{
			create_pipe(node_command_term);
			input_heredoc(node_command->value,
					node_command_term->in_fd[1], mshell);
		}
		node_command = node_command->next;
	}
	// if (node_command_term->in_fd[0] != 0)
	// {
	// 	close(node_command_term->in_fd[1]);
	// 	// dup2(node_command_term->in_fd[0],0);
	// 	// close(node_command_term->in_fd[0]);
	// }
	return (0);
}

int	add_str_to_pipe(t_ast_node *node_command_term, char *str)
{
	if (str != NULL)
	{
		create_pipe(node_command_term);
		if (write(node_command_term->in_fd[1], str, ft_strlen(str)) != (ssize_t)ft_strlen(str))
			return (perror("write add str to pipe"), 1);
		free(str);
	}
	return (0);
}

bool	add_str_to_redirections(t_ast_node *node_command_term, char *str, t_shell *mshell)
{
	t_ast_node	*node_command;
	int			output;

	node_command = node_command_term->child;
	output = 0;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE))
			output = ouput_write(node_command->value, str, mshell);
		if ((node_command->type & WRITE_APPEND))
			output = ouput_write_append(node_command->value, str, mshell);
		node_command = node_command->next;
	}
	return (output);
}

int	check_if_red_out(t_ast_node *node_command_term)
{
	t_ast_node	*node_command;
	int			output;

	node_command = node_command_term->child;
	output = 0;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE) || (node_command->type & WRITE_APPEND))
			output = 1;
		node_command = node_command->next;
	}
	return (output);
}
