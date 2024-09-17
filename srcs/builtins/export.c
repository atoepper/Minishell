/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jweingar <jweingar@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:53:41 by jweingar          #+#    #+#             */
/*   Updated: 2024/09/17 15:23:23 by jweingar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	ft_export(char **argv, t_shell *mshell, int fd)
{
	int		i;
	char	*key;
	char	*value;

	if (argv[1] == NULL)
	{
		ft_env(argv, mshell, fd);
		return (0);
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strchr(argv[i], '=') != NULL)
		{
			key = ft_getkeyword(argv[i]);
			value = ft_getvalue(argv[i]);
			if (key == NULL || value == NULL)
				return (1);
			if (ft_find_value_by_key(mshell->envlst, key) != NULL)
			{
				ft_change_envvalue(mshell->envlst, key, value);
				free(key);
			}
			else
				ft_add_env(&(mshell->envlst), ft_new_env(key, value));
		}
		i++;
	}
	return (0);
}
