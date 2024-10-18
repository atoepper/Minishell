/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:06:31 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/17 13:04:53 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

char	*ft_expand_env(t_shell *mshell, char **cursor, int type)
{
	char	*expand_to;
	char	*key;

	(*cursor)++;
	if (*(*cursor) == '?')
	{
		expand_to = ft_itoa(mshell->exit_status);
		(*cursor)++;
	}
	else if (ft_iskeyword(*cursor))
	{
		key = ft_substr(*cursor, 0, ft_end_of_varname(*cursor));
		if (ft_find_key(mshell->envlst, key))
			expand_to = ft_strdup(ft_find_value_by_key(mshell->envlst, key));
		else
			expand_to = ft_strdup("");
		free(key);
		(*cursor) += ft_end_of_varname(*cursor);
	}
	else if (*(*cursor) == '\0' && !(type & RIGHT_JOIN))
		expand_to = ft_strdup("$");
	else
		expand_to = ft_strdup("");
	return (expand_to);
}

char	*ft_no_expand(char **cursor)
{
	char	*str;
	char	*pos;

	pos = ft_strchr(*cursor, '$');
	if (pos)
	{
		str = ft_substr(*cursor, 0, pos - *cursor);
		*cursor = pos;
	}
	else
	{
		str = ft_strdup(*cursor);
		*cursor += ft_strlen(*cursor);
	}
	return (str);
}

char	*ft_expand(char *value, t_shell *mshell, int type)
{
	char	*expanded;
	char	*tmp;
	char	*insert;
	char	*cursor;

	cursor = value;
	expanded = ft_strdup("");
	while (*cursor != '\0')
	{
		if (*cursor == '$')
			insert = ft_expand_env(mshell, &cursor, type);
		else
			insert = ft_no_expand(&cursor);
		tmp = expanded;
		expanded = ft_strjoin(tmp, insert);
		free(insert);
		free(tmp);
	}
	return (expanded);
}

void	ft_unexpand_heredoc(t_token **token_list)
{
	t_token	*current;

	current = *token_list;
	while (current)
	{
		if (current->type & HEREDOC)
		{
			current = current->next;
			while (current && current->type & WORD)
			{
				current->type &= ~EXPANDER;
				if (current->type & RIGHT_JOIN)
					current = current->next;
				else
					break ;
			}
		}
		current = current->next;
	}
}

int	expander(t_shell *mshell)
{
	t_token	*current;
	char	*tmp;

	current = mshell->token_list;
	ft_unexpand_heredoc(&(mshell->token_list));
	while (current)
	{
		if (current->type & EXPANDER)
		{
			tmp = current->value;
			current->value = ft_expand(current->value, mshell, current->type);
			free(tmp);
		}
		current = current->next;
	}
	return (0);
}
