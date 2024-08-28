/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:37 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/27 13:55:37 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_ast_node	*parse_command(t_token **current_token);
t_ast_node	*parse_redir_term(t_token **current_token);
char		**create_argv(t_token **current_token, int argc);

// Parse program -> { pipe_line }
t_ast_node *parse_program(t_token **current_token)
{
	t_ast_node *program_node;
	t_ast_node *pipe_node;

	program_node = create_ast_node(PROGRAM, NULL);
	while (*current_token)
	{
		pipe_node = parse_pipe(current_token);
		if (pipe_node)
			add_child_node(program_node, pipe_node);
		else
			break;
	}
	return (program_node);
}

// Parse pipe_line -> command { '|' command }
t_ast_node *parse_pipe(t_token **current_token)
{
    t_ast_node *pipe_node;
    t_ast_node *command_term_node;

	pipe_node = create_ast_node(PIPE, NULL);
	command_term_node = parse_command(current_token);
    if (!command_term_node)
	{
        free(pipe_node);
        return NULL;
    }
    add_child_node(pipe_node, command_term_node);
    while (*current_token && (*current_token)->type & PIPE)
	{
        *current_token = (*current_token)->next; // Skip '|'
        command_term_node = parse_command_term(current_token);
        if (!command_term_node)
		{
            printf("Syntax error: Expected command after '|'\n"); // parse error??
            free(pipe_node);
            return NULL;
        }
        add_child_node(pipe_node, command_term_node);
    }
    return (pipe_node);
}

// Parse command_term -> [ command ][ redir_iter ]
t_ast_node *parse_command_term(t_token **current_token)
{
    t_ast_node *command_term_node;
	t_ast_node *redir_iter_node;
	t_ast_node *command_node;

	command_term_node = create_ast_node(COMMAND_TERM, NULL);
	redir_iter_node = parse_redir_iter(current_token);
	if (redir_iter_node)
		add_child_node(command_term_node, redir_iter_node);
	command_node = parse_command(current_token);
	if (command_node)
		add_child_node(command_term_node, command_node);
	redir_iter_node = parse_redir_iter(current_token);
	if (redir_iter_node)
		add_child_node(command_term_node, redir_iter_node);
    if (!command_term_node->child)
	{
        free(command_term_node);
        return NULL;
    }
    return (command_term_node);
}

// Parse redir_iter -> redir_term { redir_term }
t_ast_node *parse_redir_iter(t_token **current_token)
{
	t_ast_node *redir_iter_node;
	t_ast_node *redir_term_node;

	redir_iter_node = NULL;
	while (*current_token && (*current_token)->type & REDIRECT)
	{
		redir_term_node = parse_redir_term(current_token);
		if (redir_term_node) 
		{
			if (!redir_iter_node)
				redir_iter_node = create_ast_node(REDIR_ITER, NULL);
			add_child_node(redir_iter_node, redir_term_node);
		} 
		else
			break;
	}
	return (redir_iter_node);
}

// Parse redir_chunk -> redirection file_path
t_ast_node *parse_redir_term(t_token **current_token) 
{
	t_ast_node *redir_term_node;
	t_ast_node *redirection_node;

	if (!*current_token || (*current_token)->type != REDIRECT)
		return NULL;
	redir_term_node = create_ast_node(REDIR_TERM, NULL);
	redirection_node = create_ast_node(REDIRECT, (*current_token)->value);
	add_child_node(redir_term_node, redirection_node);
	*current_token = (*current_token)->next;
	// Parse file path
	if (*current_token && (*current_token)->type == WORD)
	{
		t_ast_node *file_path_node = create_ast_node(FILE_PATH, (*current_token)->value);
		add_child_node(redir_term_node, file_path_node);
		*current_token = (*current_token)->next;
	} 
	else
	{
	printf("Syntax error: Expected file path after redirection\n");
		free(redir_term_node);
		return NULL;
	}
	return (redir_term_node);
}
