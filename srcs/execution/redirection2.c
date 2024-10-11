/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:40:57 by jweingar          #+#    #+#             */
/*   Updated: 2024/10/11 10:16:06 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

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

int	create_pipe(t_ast_node *node_command_term)
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
	return (0);
}

int	add_str_to_pipe(t_ast_node *node_command_term, char *str)
{
	if (str != NULL)
	{
		create_pipe(node_command_term);
		if (write(node_command_term->in_fd[1], str,
				ft_strlen(str)) != (ssize_t)ft_strlen(str))
			return (perror("write add str to pipe"), 1);
		free(str);
	}
	return (0);
}
