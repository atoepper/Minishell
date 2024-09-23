/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:37 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/23 16:36:47 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

// <program> -> <command_term> {'|' <command_term>}
t_ast_node	*parse_program(t_shell *mshell)
{
	t_ast_node	*program_node;
	t_ast_node	*command_term_node;

	mshell->curr_token = mshell->token_list;
	program_node = create_ast_node(PROGRAM, NULL);
	command_term_node = parse_command_term(mshell);
	if (command_term_node != NULL)
		add_child_node(program_node, command_term_node);
	else
		return (free_ast(program_node), NULL);
	while (mshell->curr_token != NULL && mshell->curr_token->type & PIPE)
	{
		mshell->curr_token = mshell->curr_token->next;
		command_term_node = parse_command_term(mshell);
		if (command_term_node == NULL)
		{
			free_ast(program_node);
			ft_set_error(mshell, 1, "minishell: parse error near '|'\n");
			return (NULL);
		}
		else
			add_child_node(program_node, command_term_node);
	}
	return (program_node);
}

// <command_term> -> {<element>}
t_ast_node	*parse_command_term(t_shell *mshell)
{
	t_ast_node	*command_term_node;
	t_ast_node	*element_node;
	t_ast_node	*command_node;

	command_term_node = create_ast_node(COMMAND_TERM, NULL);
	element_node = parse_element(mshell);
	command_node = create_ast_node(COMMAND, NULL);
	while (mshell->error == 0 && element_node != NULL)
	{
		if (element_node->type & REDIRECT)
			add_child_node(command_term_node, element_node);
		else
			add_child_node(command_node, element_node);
		element_node = parse_element(mshell);
	}
	if (command_node->child != NULL)
	{
		ft_create_argv(command_node);
		add_child_node(command_term_node, command_node);
	}
	else
		free_ast(command_node);
	if (mshell->error != 0 || command_term_node->child == NULL)
		return (free_ast(command_term_node), NULL);
	return (command_term_node);
}

t_ast_node	*parse_element(t_shell *mshell)
{
	t_ast_node	*element_node;

	if (mshell->curr_token != NULL && mshell->curr_token->type & WORD)
	{
		element_node = create_ast_node(COMMAND, mshell->curr_token->value);
		mshell->curr_token = mshell->curr_token->next;
		return (element_node);
	}
	else if (mshell->curr_token != NULL && mshell->curr_token->type & REDIRECT)
	{
		if (mshell->curr_token->next != NULL
			&& mshell->curr_token->next->type & WORD)
		{
			element_node = create_ast_node(mshell->curr_token->type,
					ft_strdup(mshell->curr_token->next->value));
			mshell->curr_token = mshell->curr_token->next->next;
			return (element_node);
		}
		else
			ft_set_error(mshell, 1, "minishell:
				syntax error near unexpected token\n");
	}
	return (NULL);
}

// // <command_term> -> [<redir iteration>] [<command>] [<redir iteration>]
// t_ast_node	*parse_command_term(t_shell *mshell)
// {
// 	t_ast_node	*command_term_node;
// 	t_ast_node	*command_note;
// 	t_ast_node	*redir_iter_pre_node;
// 	t_ast_node	*redir_iter_post_node;

// 	command_term_node = create_ast_node(COMMAND_TERM, NULL);
// 	redir_iter_pre_node = parse_redir_iter(mshell);
// 	if (mshell->error == 0)
// 	{
// 		command_note = parse_command(mshell);
// 		redir_iter_post_node = parse_redir_iter(mshell);
// 		if (redir_iter_pre_node != NULL)
// 			add_branch(command_term_node, redir_iter_pre_node); 
// 		if (redir_iter_post_node != NULL)
// 			add_branch(command_term_node, redir_iter_post_node);
// 		if (command_note != NULL)
// 			add_child_node(command_term_node, command_note);
// 	}
// 	if (mshell->error != 0 || command_term_node->child == NULL)
// 	{
// 		free_ast(command_term_node);
// 		return (NULL);
// 	}
// 	return (command_term_node);
// }

// // <redirection iteration> -> <redirection term> {<redirection term}
// t_ast_node	*parse_redir_iter(t_shell *mshell)
// {
// 	t_ast_node	*redir_iter_node;
// 	t_ast_node	*redir_term_node;

// 	if (mshell->curr_token == NULL || !(mshell->curr_token->type & REDIRECT))
// 		return (NULL);
// 	redir_iter_node = create_ast_node(REDIR_ITER, NULL);
// 	redir_term_node = parse_redir_term(mshell);
// 	if (redir_term_node != NULL)
// 		add_child_node(redir_iter_node, redir_term_node);
// 	while (mshell->curr_token != NULL && mshell->curr_token->type & REDIRECT
// 		&& mshell->error == 0)
// 	{
// 		redir_term_node = parse_redir_term(mshell);
// 		if (redir_term_node != NULL)
// 			add_child_node(redir_iter_node, redir_term_node);
// 		else
// 			break ;
// 	}
// 	if (mshell->error != 0)
// 	{
// 		free_ast(redir_iter_node);
// 		return (NULL);
// 	}
// 	return (redir_iter_node);
// }

// // <redirection term> -> <redirection> <filepath>
// t_ast_node	*parse_redir_term(t_shell *mshell)
// {
// 	t_ast_node	*redir_term_node;

// 	if (mshell->curr_token->type & REDIRECT)
// 	{
// 		if (mshell->curr_token->next != NULL
// 			&& mshell->curr_token->next->type & WORD)
// 		{
// 			redir_term_node = create_ast_node(mshell->curr_token->type,
// 					ft_strdup(mshell->curr_token->next->value));
// 			mshell->curr_token = mshell->curr_token->next->next;
// 			return (redir_term_node);
// 		}
// 		else
// 			ft_set_error(mshell, 1, "minishell: syntax error near unexpected token\n");
// 	}
// 	return (NULL);
// }

// t_ast_node	*parse_command(t_shell *mshell)
// {
// 	t_ast_node	*command_node;
// 	int			argc;

// 	if (mshell->curr_token == NULL
// 		|| !(mshell->curr_token->type & WORD))
// 		return (NULL);
// 	command_node = create_ast_node(COMMAND, NULL);
// 	argc = ft_count_args(&(mshell->curr_token));
// 	command_node->argv = ft_create_argv(&(mshell->curr_token), argc);
// 	if (command_node->argv == NULL)
// 		return (NULL); /* Malloc error */
// 	while (argc-- > 0)
// 		mshell->curr_token = mshell->curr_token->next;
// 	return (command_node);
// }

