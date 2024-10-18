/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:41:34 by atoepper          #+#    #+#             */
/*   Updated: 2024/10/18 12:52:22 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_find_equal(char *str)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '=')
		index++;
	return (index);
}

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
	if (str == NULL)
		return (FALSE);
	if (*str == '\0' || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (FALSE);
	while (*str)
	{
		if (!(ft_isalnum(*str) || *str == '_'))
			return (FALSE);
		str++;
	}
	return (TRUE);
}
