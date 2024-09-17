/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:02:29 by atoepper          #+#    #+#             */
/*   Updated: 2024/09/17 15:21:32 by jweingar         ###   ########.fr       */
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

bool	is_output_without_nl(t_shell *mshell)
{
	char	*str;

	str = mshell->last_output;
	if (str == NULL)
		return(FALSE);
	while (*str != '\0')
		str++;
	if (--*str == '\n')
		return(FALSE);
	else
		return(TRUE);
}
