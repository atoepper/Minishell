/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:02:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 10:17:05 by atoepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

bool	ft_isseparator(const char c)
{
	if (c == ' ' || c == '\0' || c == '\t' || c == '\n' \
	|| c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	ft_skipspaces(char **line)
{
	while (*line && (**line == ' ' || **line == '\t' || **line == '\n'))
		(*line)++;
}

bool	ft_string_is_empty(char *str)
{
	if (!str)
		return (TRUE);
	while (*str)
	{
		if (*str != ' ' || *str != '\t' || *str != '\n')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
