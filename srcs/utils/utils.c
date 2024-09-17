/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:41:34 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/09 11:03:06 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_nextchar(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != c)
		index++;
	if (str[index] == '\0' && c != '\0')
		return (-1);
	return (index);
}

int	ft_end_of_varname(char *str)
{
	int	index;

	index = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[index] && (ft_isalnum(str[index]) || str[index] == '_'))
			index++;
	}
	return (index);
}

int	ft_wordlength(char *line)
{
	int	len;

	len = 0;
	while (!(line[len] == '\'' || line[len] == '\"' \
	|| line[len] == ' ' || line[len] == '\0' \
	|| line[len] == '\t' || line[len] == '\n' \
	|| line[len] == '|' || line[len] == '<' || line[len] == '>'))
		len++;
	return (len);
}

bool	ft_iskeyword(char *str)
{
	if (*str && ft_isalpha(str[0]))
		return (TRUE);
	else if (*str && *str == '_')
	{
		while (*str == '_')
			str++;
		if (ft_isalnum(*str))
			return (TRUE);
	}
	return (FALSE);
}
