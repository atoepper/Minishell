/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:37 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/04 10:42:20 by atoepper         ###   ########.fr       */
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
		if (command_term_node)
			add_child_node(program_node, command_term_node);
	while (mshell->curr_token && mshell->curr_token->type & PIPE)
	{
		mshell->curr_token = mshell->curr_token->next;
		command_term_node = parse_command_term(mshell);
		if (!command_term_node)
		{
			printf("Syntax error: Expected command after '|'");
			free_ast(program_node);
			return (NULL);
		}
		else
			add_child_node(program_node, command_term_node);
	}
	return (program_node);
}
// <command_term> -> [<redirection iteration>] [<command>] [<redirection iteration>]
t_ast_node	*parse_command_term(t_shell *mshell)
{
	t_ast_node	*command_term_node;
	t_ast_node	*command_note;
	t_ast_node	*redir_iter_pre_node;
	t_ast_node	*redir_iter_post_node;

	command_term_node = create_ast_node(COMMAND_TERM, NULL);
	redir_iter_pre_node = parse_redir_iter(mshell);
	if (mshell->error == 0)
	{
		command_note = parse_command(mshell);
		redir_iter_post_node = parse_redir_iter(mshell);		
		if (redir_iter_pre_node)
			add_child_node(command_term_node, redir_iter_pre_node);
		if (redir_iter_post_node)
			add_child_node(command_term_node, redir_iter_post_node);
		if (command_note)
			add_child_node(command_term_node, command_note);
	}
	if (mshell->error != 0)
	{
		free_ast(command_term_node);
		return NULL;
	}
	return (command_term_node);
}

// <redirection iteration> -> <redirection term> {<redirection term}
t_ast_node	*parse_redir_iter(t_shell *mshell)
{
	t_ast_node	*redir_iter_node;
	t_ast_node	*redir_term_node;

	if (!mshell->curr_token || !(mshell->curr_token->type & REDIRECT))
		return NULL;
	redir_iter_node = create_ast_node(REDIR_ITER, NULL);
	redir_term_node = parse_redir_term(mshell);
	if (redir_term_node)
		add_child_node(redir_iter_node, redir_term_node);
	while (mshell->curr_token && mshell->curr_token->type & REDIRECT 
		&& mshell->error == 0)
	{
		redir_term_node = parse_redir_term(mshell);
		if (redir_term_node)
			add_child_node(redir_iter_node, redir_term_node);
		else
			break ;
	}
	if (mshell->error != 0)
	{
		free_ast(redir_iter_node);
		return (NULL);
	}
	return (redir_iter_node);	
}

// <redirection term> -> <redirection> <filepath>
t_ast_node	*parse_redir_term(t_shell *mshell)
{
	t_ast_node	*redir_term_node;

	if (mshell->curr_token->type & REDIRECT)
	{
		if (mshell->curr_token->next->type & WORD)
		{
			redir_term_node = create_ast_node(mshell->curr_token->type,
				ft_strdup(mshell->curr_token->next->value));
			mshell->curr_token = mshell->curr_token->next->next;
			return (redir_term_node);			
		}
		else
			ft_set_error(mshell, 1, "minishell: syntax error near unexpected token\n");
	}
	return (NULL);
}

t_ast_node	*parse_command(t_shell *mshell)
{
	t_ast_node	*command_node;
	int			argc;

	if (!mshell->curr_token || !(mshell->curr_token->type & WORD))
		return NULL;
	command_node = create_ast_node(COMMAND, NULL);
	argc = ft_count_args(&(mshell->curr_token));
	command_node->argv = ft_create_argv(&(mshell->curr_token), argc);
	while (argc-- > 0)
		mshell->curr_token = mshell->curr_token->next;
	return (command_node);
}


/* git status uberprufen und aktualisieren, Tagebuch aktualisieren */


// // <program> -> <command_term> {'|' <command_term>}
// t_ast_node	*parse_program(t_token **current)
// {
// 	t_ast_node	*program_node;
// 	t_ast_node	*command_term_node;

// 	program_node = create_ast_node(PROGRAM, NULL);
// 	command_term_node = parse_command_term(current);
// 		if (command_term_node)
// 			add_child_node(program_node, command_term_node);
// 	while (*current && (*current)->type & PIPE)
// 	{
// 		*current = (*current)->next;
// 		command_term_node = parse_command_term(current);
// 		if (!command_term_node)
// 		{
// 			printf("Syntax error: Expected command after '|'");
// 			free_ast(program_node);
// 			return (NULL);
// 		}
// 		else
// 			add_child_node(program_node, command_term_node);
// 	}
// 	return (program_node);
// }
// // <command_term> -> [<redirection iteration>] [<command>] [<redirection iteration>]
// t_ast_node	*parse_command_term(t_token **current)
// {
// 	t_ast_node	*command_term_node;
// 	t_ast_node	*command_note;
// 	t_ast_node	*redir_iter_pre_node;
// 	t_ast_node	*redir_iter_post_node;

// 	command_term_node = create_ast_node(COMMAND_TERM, NULL);
// 	redir_iter_pre_node = parse_redir_iter(current);
// 	command_note = parse_command(current);
// 	redir_iter_post_node = parse_redir_iter(current);
// 	/* error handling ??*/
// 	if (redir_iter_pre_node)
// 		add_child_node(command_term_node, redir_iter_pre_node);
// 	if (redir_iter_post_node)
// 		add_child_node(command_term_node, redir_iter_post_node);
// 	if (command_note)
// 		add_child_node(command_term_node, command_note);
// 	 if (!command_term_node->child)
// 	{
// 		free_ast(command_term_node);
// 		return NULL;
// 	}
// 	return (command_term_node);
// }

// // <redirection iteration> -> <redirection term> {<redirection term}
// t_ast_node	*parse_redir_iter(t_token **current)
// {
// 	t_ast_node	*redir_iter_node;
// 	t_ast_node	*redir_term_node;

// 	if (!*current || !((*current)->type & REDIRECT))
// 		return NULL;
// 	redir_iter_node = create_ast_node(REDIR_ITER, NULL);
// 	redir_term_node = parse_redir_term(current);
// 	if (redir_term_node)
// 		add_child_node(redir_iter_node, redir_term_node);
// 	while (*current && (*current)->type & REDIRECT)
// 	{
// 		redir_term_node = parse_redir_term(current);
// 		if (redir_term_node)
// 			add_child_node(redir_iter_node, redir_term_node);
// 		else
// 			break ;
// 	}
// 	if (!redir_iter_node->child)
// 	{
// 		free_ast(redir_iter_node);
// 		return (NULL);
// 	}
// 	return (redir_iter_node);	
// }

// // <redirection term> -> <redirection> <filepath>
// t_ast_node	*parse_redir_term(t_token **current)
// {
// 	t_ast_node	*redir_term_node;

// 	if ((*current)->type & REDIRECT)
// 	{
// 		if ((*current)->next->type & WORD)
// 		{
// 			redir_term_node = create_ast_node((*current)->type, ft_strdup((*current)->next->value));
// 			*current = (*current)->next->next;
// 			return (redir_term_node);			
// 		}
// 		else
// 			printf("minishell: syntax error near unexpected token\n");
// 	}
// 	return (NULL);
// }

// t_ast_node	*parse_command(t_token **current)
// {
// 	t_ast_node	*command_node;
// 	int			argc;

// 	if (!*current || !((*current)->type & WORD))
// 		return NULL;
// 	command_node = create_ast_node(COMMAND, NULL);
// 	argc = ft_count_args(current);
// 	command_node->argv = ft_create_argv(current, argc);
// 	while (argc-- > 0)
// 		*current = (*current)->next;
// 	return (command_node);
// }
