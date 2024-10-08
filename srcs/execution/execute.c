/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:09:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/08 15:59:59 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	print_and_save_str(t_shell *mshell, char *str)
{
	mshell->last_output = str;
	ft_putstr_fd(str, 1);
}


int	check_output_fd(t_ast_node *node_command_term)
{
	if (node_command_term->next != NULL || check_if_red_out(node_command_term) == 1)
	{
		if (pipe(node_command_term->out_fd) == -1)
			return (perror("pipe"), 1);
	}
	return (0);
}



int	execute_command_term(t_shell *mshell,
			t_ast_node *node_command_term, char *str)
{
	add_str_to_pipe(node_command_term, str);
	add_redirection_to_pipe(node_command_term, mshell);
	check_redirection_output(node_command_term, mshell);
	check_output_fd(node_command_term);
	if (mshell->error == 0)
	{
		exec_function(node_command_term, mshell);
		if (node_command_term->out_fd[1] != 1)
		{
			str = read_fd_to_str(node_command_term);
			add_str_to_redirections(node_command_term, str, mshell);
		}
	}
	else
		str = NULL;
	if (node_command_term->next != NULL)
		execute_command_term(mshell, node_command_term->next, str);
	else
		free(str);
	return (0);
}


int	execute_programm(t_shell *mshell)
{
	t_ast_node	*node_command_term;

	if (mshell->ast == NULL)
		return (1);
	node_command_term = mshell->ast->child;
	if (node_command_term != NULL)
		execute_command_term(mshell, node_command_term, NULL);
	return (0);
}
