/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linetolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:24:04 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/15 12:57:15 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_skipspaces(char **line)
{
	while (*line && **line == ' ')
		(*line)++;
}

int	ft_nextchar(char *str, char c)
{
	int index;

	index = 0;
	while (str[index] && str[index] != c)
		index++;
	if (str[index] == '\0' && c != '\0')
		return (-1);
	return (index);
}

t_token *ft_newquote(char **line)
{
	t_token	*new;
	char	*line_ptr;
	int		len;

	line_ptr = *line;
	if ((*line_ptr == '\"' && !ft_strchr(line_ptr + 1, '\"')) ||  
		(*line_ptr == '\'' && !ft_strchr(line_ptr + 1, '\'')))
			return (/* set error */ NULL);
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
	new = ft_newtoken("", REDIRECT);
	if (!new)
		return(/* malloc error */NULL);
	if (!ft_strncmp(*line_ptr, "<<", 2))
		new->type |= HEREDOC;
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		new->type |= WRITE_APPEND;
	else if (*line_ptr == '<')
		new->type |= READ;
	else if (*line_ptr == '>')
		new->type |= WRITE;	
	if (new->type & (HEREDOC | WRITE_APPEND))
		(*line) += 2;
	else
		(*line) += 1;
	return (new); 
}

t_token *ft_newpipe(char **line)
{
	t_token	*new;
	new = ft_newtoken("|", PIPE);
	return (new); 
}

t_token *ft_newword(char **line)
{
	
}


t_token *ft_linetolist(char *line, int *error)
{
	int		error;
	t_token	*list;
	t_token	*new;

	list = NULL;
	while (*line)
	{
		ft_skipspaces(line);
		if (*line == '\'' || *line == '\"')
			/* read quotes */
		if (*line == '<' || *line == '>')
			/* read redirection < << >> > | */
		if (*line == '|')
			/* read pipe */
		else
			/* read word */
		/* append token to list */
	}
	return (list);
}