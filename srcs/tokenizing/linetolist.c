/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linetolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:24:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/19 16:06:18 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_token *ft_newquote(char **line)
{
	t_token	*new;
	char	*line_ptr;
	int		len;

	line_ptr = *line;
	if ((*line_ptr == '\"' && !ft_strchr(line_ptr + 1, '\"')) ||  
		(*line_ptr == '\'' && !ft_strchr(line_ptr + 1, '\'')))
			return (/* error */ printf("open quotes\n"), NULL);
	len = ft_nextchar(line_ptr + 1, (*line_ptr == '\'') * '\''
		+ (*line_ptr == '\"') * '\"');
	new = ft_newtoken(ft_substr(line_ptr, 1, len),
		((*line_ptr == '\'') * SQUOTE | (*line_ptr == '\"') * DQUOTE | WORD));
	if (ft_strchr(new->value, '$') && new->type & DQUOTE)
		new->type |= EXPANDER;
	(*line)+= len + 2;
	return (new); 
}

t_token *ft_newredirection(char **line)
{
	t_token	*new;
	char	*line_ptr;

	line_ptr = *line;
	new = ft_newtoken(NULL, REDIRECT);
	if (!new)
		return(/* malloc error */NULL);
	if (!ft_strncmp(line_ptr, "<<", 2))
		new->type |= HEREDOC;
	else if (!ft_strncmp(line_ptr, ">>", 2))
		new->type |= WRITE_APPEND;
	else if (*line_ptr == '<')
		new->type |= READ;
	else if (*line_ptr == '>')
		new->type |= WRITE;	
	if (new->type & (HEREDOC | WRITE_APPEND))
		(*line) += 2;
	else
		(*line) += 1;
	// printf("value test: %s, %d\n", new->value, new->type);
	return (new); 
}

t_token *ft_newpipe(char **line)
{
	t_token	*new;

	new = ft_newtoken(NULL, PIPE);
	if (!new)
		return (/* error malloc */ NULL);
	(*line)++;
	return (new); 
}

t_token *ft_newword(char **line)
{
	t_token	*new;
	char	*word;
	char	*line_ptr;

	line_ptr = *line;
	word = ft_substr(line_ptr, 0, ft_wordlength(line_ptr));
	new = ft_newtoken(word, WORD);
	if (!new)
		return (/* malloc error */ NULL);
	if (ft_strchr(new->value, '$'))
		new->type |= EXPANDER;
	(*line) += ft_wordlength(line_ptr);
	return(new);
}


t_token *ft_linetolist(char *line, int *error)
{
	t_token	*list;
	t_token	*new;

	(void)error;
	list = NULL;
	ft_skipspaces(&line);
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			new = ft_newquote(&line);
		else if (*line == '<' || *line == '>')
			new = ft_newredirection(&line);
		else if (*line == '|')
			new = ft_newpipe(&line);
		else
			new = ft_newword(&line);
		if (!new)
			return(ft_clear_tokenlist(&list), NULL);
		if (new->type & WORD && !ft_isseparator(*line))
			new->type |= RIGHT_JOIN;
		ft_skipspaces(&line);
		ft_addtoken(&list, new);
	}
	return (list);
}

int	ft_joinwords(t_token **list)
{
	t_token *current;
	t_token	*tmp;
	char	*joint;
 	
	current = *list;
	while (current->next != NULL)
	{
		if (current->type & RIGHT_JOIN)
		{
			joint = ft_strjoin(current->value, current->next->value);
			if (!joint)
				return (/* handle error */ 1);
			free(current->value);
			current->value = joint;
			if (!(current->next->type & RIGHT_JOIN))
				current->type &= ~RIGHT_JOIN;
			tmp = current->next;
			current->next = current->next->next;
			ft_deltoken(tmp);
		}
		else 
			current = current->next;	
	}
	return (0);
}
