/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:41:34 by atoepper          #+#    #+#             */
/*   Updated: 2024/08/19 15:19:30 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	ft_skipspaces(char **line)
{
	while (*line && (**line == ' ' || **line == '\t' || **line == '\n'))
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

bool	ft_isseparator(const char c)
{
	if (c == ' ' || c == '\0' || c == '\t' || c == '\n' \
	|| c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}