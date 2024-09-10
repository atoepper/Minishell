/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:55:26 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/10 16:39:39 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*input_read(char *input, char *str)
{
	int		fd_input;
	char	buf[2];
	char	*new_str;

	buf[1] = '\0';
	fd_input = open(input, O_RDONLY);
	while (read(fd_input, buf, 1) == 1)
	{
		new_str = ft_strjoin(str, buf);
		if (new_str == NULL)
			return (free(str), NULL);
		free(str);
		str = new_str;
	}
	return (str);
}

char	*input_heredoc(char *input, char *str)
{
	char	buf[1024];
	int		read_return;
	char	*new_str;

	ft_bzero(buf, 1024);
	input = ft_strjoin(input, "\n");
	if (input == NULL)
		return (perror("ft_strjoin"), NULL);
	read_return = read(0, buf, 1024);
	buf[read_return] = '\0';
	while (ft_strncmp(buf, input, ft_strlen(input)) != 0)
	{
		new_str = ft_strjoin(str, buf);
		if (new_str == NULL)
			return (free(str), NULL);
		free(str);
		ft_bzero(buf, 1024);
		read_return = read(0, buf, 1024);
		buf[read_return] = '\0';
		str = new_str;
	}
	return (str);
}

int	ouput_write(char *path, char *str)
{
	int	fd_output;
	int	write_return;

	fd_output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_return = write(fd_output, str, ft_strlen(str));
	if (write_return != -1)
		return (0);
	return (1);
}

int	ouput_write_append(char *path, char *str)
{
	int	fd_output;

	fd_output = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (write(fd_output, str, ft_strlen(str)) != -1)
		return (0);
	return (1);
}

char	*read_fd_to_str(int fd)
{
	char	buf[2];
	char	*str;
	char	*new_str;
	int		result;

	str = NULL;
	result = 0;
	buf[1] = '\0';
	while (read(fd, buf, 1) == 1)
	{
		new_str = ft_strjoin(str, buf);
		if (new_str == NULL)
			return (free(str), NULL);
		free(str);
		str = new_str;
	}
	close(fd);
	result++;
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

int	add_redirection_to_pipe(t_ast_node *node_command_term, char *str, int fd)
{
	t_ast_node	*node_command;

	node_command = node_command_term->child;
	while ((node_command != NULL))
	{
		if ((node_command->type & READ))
			str = input_read(node_command->value, str);
		else if ((node_command->type & HEREDOC))
			str = input_heredoc(node_command->value, str);
		node_command = node_command->next;
	}
	if (str != NULL)
		write_str_to_fd(str, fd);
	free(str);
	close(fd);
	return (0);
}

int	add_str_to_redirections(t_ast_node *node_command_term, char *str)
{
	t_ast_node	*node_command;
	int			output;

	node_command = node_command_term->child;
	output = 1;
	while ((node_command != NULL))
	{
		if ((node_command->type & WRITE))
			output = ouput_write(node_command->value, str);
		if ((node_command->type & WRITE_APPEND))
			output = ouput_write_append(node_command->value, str);
		node_command = node_command->next;
	}
	return (output);
}

// int	redirection_test(int input_typ, char *input, int output_typ, char *output)
// {
// 	int		fd_input;
// 	int		fd_output;
// 	char	buf[1];
// 	int		count_read;

// 	fd_input = -1;
// 	fd_output = -1;
// 	ft_bzero(buf, ft_strlen(buf));
// 	if (input_typ == 0)
// 		fd_input = input_redirection(input);
// 	else if (input_typ == 1)
// 		fd_input = here_document(input);
// 	if (fd_input == -1)
// 		return(perror("fd_input"), 1);
// 	fd_output = ouput_redirection(output_typ, output);
// 	if (fd_output == -1)
// 		return(perror("fd_output"), 1);
// 	count_read = read(fd_input, buf, 1);
// 	while (count_read != 0)
// 	{
// 		ft_putstr_fd(buf, fd_output);
// 		count_read = read(fd_input, buf, 1);
// 	}
// 	close(fd_input);
// 	close(fd_output);
// 	return (0);
// }

// int	main(void)
// {

// 	redirection_test(0, "../../testing/test.txt", 0, "../../testing/test1.txt");
// 	redirection_test(0, "../../testing/test.txt", 1, "../../testing/test2.txt");
// 	redirection_test(1, "EOF", 0, "../../testing/test3.txt");
// 	redirection_test(1, "EOF", 1, "../../testing/test4.txt");
// 	return (0);
// }
